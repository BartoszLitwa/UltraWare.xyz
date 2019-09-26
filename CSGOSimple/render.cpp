#include "render.hpp"

#include <mutex>
#include "features/visuals.hpp"
#include "valve_sdk/csgostructs.hpp"
#include "helpers/input.hpp"
#include "menu.hpp"
#include "options.hpp"
#include "fonts/fonts.hpp"
#include "helpers/math.hpp"
#include "features/Ragebot.hpp"
#include "features/SpotMarkers.hpp"
#include "features/Hitmarker.hpp"
#include "features/LogEvents.hpp"
#include "features/bhop.hpp"

ImFont* g_pDefaultFont;
ImFont* g_pSecondFont;

ImDrawListSharedData _data;

std::mutex render_mutex;

void Render::Initialize()
{
	ImGui::CreateContext();


	ImGui_ImplWin32_Init(InputSys::Get().GetMainWindow());
	ImGui_ImplDX9_Init(g_D3DDevice9);

	draw_list = new ImDrawList(ImGui::GetDrawListSharedData());
	draw_list_act = new ImDrawList(ImGui::GetDrawListSharedData());
	draw_list_rendering = new ImDrawList(ImGui::GetDrawListSharedData());

	GetFonts();
}

void Render::GetFonts() {

	// menu font
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Droid_compressed_data,
		Fonts::Droid_compressed_size,
		14.f);
	
	// esp font
	g_pDefaultFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Droid_compressed_data,
		Fonts::Droid_compressed_size,
		18.f);
	

	// font for watermark; just example
	g_pSecondFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
		Fonts::Cousine_compressed_data,
		Fonts::Cousine_compressed_size,
		18.f); 
}

void Render::ClearDrawList() {
	render_mutex.lock();
	draw_list_act->Clear();
	render_mutex.unlock();
}

void Render::BeginScene() {
	draw_list->Clear();
	draw_list->PushClipRectFullScreen();

	int screen_w, screen_h;
	g_EngineClient->GetScreenSize(screen_w, screen_h);

	if (g_Options.misc_watermark)
		Render::Get().RenderText("UltraWare.xyz", 10, 5, 18.f, g_Options.color_watermark, false, true, g_pSecondFont);

	//if (g_EngineClient->IsInGame() && g_LocalPlayer && g_Options.Aimbot_ShowFOV)
		//Render::Get().RenderCircle(screen_w / 2, screen_h / 2, g_Options.Aimbot_FOV, 0, Color(255,255,255, 255));

	if (g_EngineClient->IsInGame() && g_LocalPlayer && g_Options.esp_enabled)
		Visuals::Get().AddToDrawList();

	if (g_EngineClient->IsInGame() && g_LocalPlayer && (g_LocalPlayer->m_bIsScoped()) && g_Options.misc_RemoveScope) {
		Render::Get().RenderLine(screen_w / 2, 0, screen_w / 2, screen_h, Color(15, 15, 15, 255)); //Vertical Line
		Render::Get().RenderLine(0, screen_h / 2, screen_w, screen_h / 2, Color(15, 15, 15, 255)); //Horizontal Line
		ConVar* postprocess = g_CVar->FindVar("mat_postprocess_enable");
		postprocess->SetValue(0);
	}

	if (g_Options.misc_SpotMarkers) {
		if (InputSys::Get().IsKeyDown(VK_F3))
			spotmarkers->button_clicked = true;
	
		spotmarkers->Update();
	}

	if (g_Options.AutoWall_ShowDamage && g_EngineClient->IsInGame() && g_LocalPlayer) {
		      // %.2f for rounding to 2 decimals
		char dmg[24]; sprintf(dmg, "%.2f", ragebot.DamageForESP);
		Render::Get().RenderText( dmg, screen_w / 2 + 10, screen_h / 2 + 10, 14, Color(255, 0, 0), false, true, g_pSecondFont);
	}

	hitmarker->paint(screen_w / 2, screen_h /2);

	logevents.Draw(screen_w, screen_h);
	logevents.DrawSteps(screen_w, screen_h);

	MISC::SpectatorList(screen_w, screen_h);

	render_mutex.lock();
	*draw_list_act = *draw_list;
	render_mutex.unlock();
}

ImDrawList* Render::RenderScene() {

	if (render_mutex.try_lock()) {
		*draw_list_rendering = *draw_list_act;
		render_mutex.unlock();
	}

	return draw_list_rendering;
}


float Render::RenderText(const std::string& text, ImVec2 pos, float size, Color color, bool center, bool outline, ImFont* pFont)
{
	ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, text.c_str());
	if (!pFont->ContainerAtlas) return 0.f;
	draw_list->PushTextureID(pFont->ContainerAtlas->TexID);

	if (center)
		pos.x -= textSize.x / 2.0f;

	if (outline) {
		draw_list->AddText(pFont, size, ImVec2(pos.x + 1, pos.y + 1), GetU32(Color(0, 0, 0, color.a())), text.c_str());
		draw_list->AddText(pFont, size, ImVec2(pos.x - 1, pos.y - 1), GetU32(Color(0, 0, 0, color.a())), text.c_str());
		draw_list->AddText(pFont, size, ImVec2(pos.x + 1, pos.y - 1), GetU32(Color(0, 0, 0, color.a())), text.c_str());
		draw_list->AddText(pFont, size, ImVec2(pos.x - 1, pos.y + 1), GetU32(Color(0, 0, 0, color.a())), text.c_str());
	}

	draw_list->AddText(pFont, size, pos, GetU32(color), text.c_str());

	draw_list->PopTextureID();

	return pos.y + textSize.y;
}

void Render::RenderCircle3D(Vector position, float points, float radius, Color color)
{
	float step = (float)M_PI * 2.0f / points;

	for (float a = 0; a < (M_PI * 2.0f); a += step)
	{
		Vector start(radius * cosf(a) + position.x, radius * sinf(a) + position.y, position.z);
		Vector end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y, position.z);

		Vector start2d, end2d;
		if (g_DebugOverlay->ScreenPosition(start, start2d) || g_DebugOverlay->ScreenPosition(end, end2d))
			return;

		RenderLine(start2d.x, start2d.y, end2d.x, end2d.y, color);
	}
}
