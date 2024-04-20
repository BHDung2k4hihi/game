#include"stdafx.h"
#include"CommonFunc.h"
#include"BaseObject.h"
#include"game_map.h"
#include"MainObject.h"
#include"ImpTimer.h"
#include"ThreatsObject.h"
#include"ExplosionObject.h"
#include"TextObject.h"
#include"BossObject.h"
#include"Geometric.h"
#include"PlayerPower.h"
#include"FlyObject.h"


BaseObject menu;
BaseObject g_background;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0)
		return false;

	/*if (TTF_Init() == -1)
	{
		success = false;

	}*/

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HIGHT,
		SDL_WINDOW_SHOWN);

	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}

		if (TTF_Init() != 0)
	    {
		   success = false;
	    }
		font_time = TTF_OpenFont("font//Starcraft Normal.ttf",15);
		if (font_time == NULL)
		{
			success = false;
		}
		font_menu = TTF_OpenFont("font//Starcraft Normal.ttf", 15);
		if (font_menu == NULL)
		{
			success = false;
		}
		/*if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4069) != 0)
		{
			return false;
		}
	    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4069);
	    g_sound_bullet[0] = Mix_LoadWAV("vu_no.wav");
		g_sound_exp[0] = Mix_LoadWAV("suriken.wav");

		 if (g_sound_bullet[0] == NULL || g_sound_exp[0] == NULL)
		{
			return false;
		}*/
	}
		return success;

}
//bool LoadMennuBackground()
//{
//	bool ret = menu.LoadImg("menu.png", g_screen);
//	if (ret == false)
//	{
//		return false;
//	}
//	return true;
//}
bool LoadBackground()
{
	bool ret = g_background.LoadImg("BRG.png", g_screen);
	if (ret == false)
		return false;


	return true;

}



void Close()
{
	g_background.Free();
	
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}
std::vector<FlyObject*> MakeFlyThreatsList()
{
	std::vector<FlyObject*> list_flythreats;

	FlyObject* dynamic_threats = new FlyObject[8];
	for (int i = 0; i < 5; i++)
	{
		FlyObject* p_threat = (dynamic_threats + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("FlyObject_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_x_pos(i * 2000 + 1600);
			p_threat->set_y_pos(50);
			BulletObject* p_bullet = new BulletObject();
			p_threat->InitBullet(p_bullet, g_screen);
			list_flythreats.push_back(p_threat);
		}
	}

	return list_flythreats;
}

std::vector<ThreatsObject*> MakeThreadList()
{
	std::vector<ThreatsObject*> list_threats;

	ThreatsObject* dynamic_threats = new ThreatsObject[30];
	for (int i = 0; i < 30; i++)
	{
		ThreatsObject* p_threat = (dynamic_threats + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("threat_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
			p_threat->set_x_pos(400 + i*300);
			p_threat->set_y_pos(200);

			int pos1 = p_threat->get_x_pos() - 100;
			int pos2 = p_threat->get_x_pos() + 100;
			p_threat->SetAnimationPos(pos1, pos2);
			p_threat->set_input_left(1);

			list_threats.push_back(p_threat);
		}
	}

	ThreatsObject* threats_objs = new ThreatsObject[30];

	for (int i = 0; i < 30; i++)
	{
		ThreatsObject* p_threat = (threats_objs + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("threat_level_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_x_pos(550 + i*900);
			p_threat->set_y_pos(250);
			p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
			p_threat->set_input_left(0);
			BulletObject* p_bullet = new BulletObject();
			p_threat->InitBullet(p_bullet, g_screen);

			list_threats.push_back(p_threat);
		}

	}


	return list_threats;
}

Mix_Chunk* g_sound_bullet[2];
Mix_Chunk* g_sound_exp[2];



int main(int argc, char* argv[])
{
	ImpTimer fps_timer;

	if (InitData() == false)

		return -1;

	//if (LoadMennuBackground() == false)

		//return -1;

	if (LoadBackground() == false)

		return -1;
	Mix_PlayChannel(-1, g_sound_bullet[0], 0);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4069);
	
	g_sound_bullet[0] = Mix_LoadWAV("vu_no.wav");
	g_sound_exp[0] = Mix_LoadWAV("suriken.wav");

	if (g_sound_bullet[0] == NULL || g_sound_exp[0] == NULL)
	{
		return false;
	}

	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);


	MainObject p_player;
	p_player.LoadImg("player_right.png", g_screen);
	p_player.set_clips();

	PlayerPower player_power;
	player_power.Init(g_screen);

	PlayerMoney player_money;
	player_money.Init(g_screen);
	player_money.SetPos(SCREEN_WIDTH * 0.5 - 300, 8);

	std::vector<ThreatsObject*> threats_list = MakeThreadList();

	BossObject bossObject;
	bool ret = bossObject.LoadImg("boss_objcet.png",g_screen);
	bossObject.set_clips();
	int xPosBoss = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6;
	bossObject.set_xpos(xPosBoss);
	bossObject.set_ypos(10);


	ExplosionObject exp_threat;
	bool tRet = exp_threat.LoadImg("exp3.png", g_screen);
	if (!tRet) return -1;
	exp_threat.set_clip();

	ExplosionObject exp_main;
	bool mRet = exp_main.LoadImg("exp3.png", g_screen);
	exp_main.set_clip();
	if (!mRet) return -1;

	int num_die = 0;

	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);

	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);
	UINT mark_value = 0;

	TextObject money_count;
	money_count.SetColor(TextObject::WHITE_TEXT);

	TextObject start_button;
	TextObject guide_button;
	TextObject quit_button;

	bool is_menu = true;
	bool start = true;
	bool is_start = true;
	bool quit = false;
	bool is_quit = false;
	bool time = false;
	bool tmp_time = false;
	Uint32 time_menu = 0;

	//Mix_PlayChannel(-1, g_sound_bullet[0], 0);

	while (start && !is_quit)
	{
		fps_timer.start();

		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				//is_start = false;
				is_quit = true;
			}

			p_player.HandelInputAction(g_event, g_screen);
		}
		SDL_SetRenderDrawColor(g_screen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
		SDL_RenderClear(g_screen);


		
		//if (is_menu == )
		//{

		//	SDL_Texture* gBackgroundTexture = menu.GetObject();
		//	SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HIGHT };
		//	//SDL_SetTextureBlendMode(gBackgroundTexture, SDL_BLENDMODE_MOD);
		//	SDL_RenderCopy(g_screen, gBackgroundTexture, NULL, &backgroundRect);

		//	//renderStart(new_texture);


		//	int mouseX, mouseY;
		//	SDL_GetMouseState(&mouseX, &mouseY);

		//	start_button.SetText("START");
		//	guide_button.SetText("GUIDE");
		//	quit_button.SetText("QUIT");

		//	start_button.LoadFromRenderText(font_menu, g_screen);
		//	if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 / 2 - 15 && mouseY <= 480 / 2 + 37 - 15) {
		//		start_button.SetColor(TextObject::GRAY_TEXT);
		//		if (g_event.type == SDL_MOUSEBUTTONDOWN) {
		//			if (g_event.button.button == SDL_BUTTON_LEFT)
		//			{
		//				start = true;
		//				is_menu = false;
		//				time = true;
		//				if (tmp_time == false)
		//				{
		//					time_menu = SDL_GetTicks() / 1000;
		//					tmp_time = true;
		//				}
		//			}
		//		}
		//	}
		//	else
		//	{

		//		start_button.SetColor(TextObject::RED_TEXT);
		//	}

		//	start_button.RenderText(g_screen, 1280 / 2 - 40, 480 / 2);

		//	guide_button.LoadFromRenderText(font_menu, g_screen);
		//	if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 / 2 - 15 + 50 && mouseY <= 480 / 2 + 37 - 15 + 50)
		//	{
		//		guide_button.SetColor(TextObject::GRAY_TEXT);

		//	}
		//	else
		//	{
		//		guide_button.SetColor(TextObject::RED_TEXT);
		//	}
		//	guide_button.RenderText(g_screen, 1280 / 2 - 40 + 2, 480 / 2 + 56);

		//	quit_button.LoadFromRenderText(font_menu, g_screen);
		//	if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 / 2 - 15 + 120 && mouseY <= 480 / 2 + 37 - 15 + 120)
		//	{
		//		quit_button.SetColor(TextObject::GRAY_TEXT);
		//		if (g_event.type == SDL_MOUSEBUTTONDOWN)
		//		{
		//			if (g_event.button.button == SDL_BUTTON_LEFT)
		//			{
		//				is_quit = true;
		//			}
		//		}
		//	}
		//	else
		//	{
		//		quit_button.SetColor(TextObject::RED_TEXT);
		//	}
		//	quit_button.RenderText(g_screen, 1280 / 2 - 40 + 5, 480 / 2 + 114);

		//	SDL_RenderPresent(g_screen);
		//	SDL_Delay(100);
		//}
	
			g_background.Render(g_screen, NULL);
			Map map_data = game_map.getMap();

			p_player.HandleBullet(g_screen);
			p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
			p_player.DoPlayer(map_data);
			p_player.Show(g_screen);


			game_map.SetMap(map_data);
			game_map.DrawMap(g_screen);

			GeometricFormat rectang_size(0, 0, SCREEN_WIDTH, 40);
			ColorData color_data(0, 80, 150);
			Geometric::RenderRectangle(rectang_size, color_data, g_screen);

			GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38);
			ColorData color_data2(255, 255, 255);

			Geometric::RenderOutline(outLineSize, color_data2, g_screen);

			player_power.Show(g_screen);
			player_money.Show(g_screen);

			int money_value = 100;

			struct MoneyDrop
			{
				int x;
				int y;
			};

			for (int i = 0; i < threats_list.size(); i++)
			{
				ThreatsObject* p_threat = threats_list.at(i);
				if (p_threat != NULL)
				{
					p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
					p_threat->ImpMoveType(g_screen);
					p_threat->DoPlayer(map_data);
					p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HIGHT);
					if (p_threat->get_type_move() == 0)
					{
						p_threat->tracking_player(map_data, p_player.get_xpos(), p_player.get_ypos());
					}
					p_threat->Show(g_screen);
					p_threat->get_player_rect (p_player.GetRect());


					SDL_Rect rect_player = p_player.GetRectFrame();
					bool bCol1 = false;
					std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
					for (int jj = 0; jj < tBullet_list.size(); jj++)
					{

						BulletObject* pt_bullet = tBullet_list.at(jj);
						if (pt_bullet)
						{
							bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
							if (bCol1)
							{
								p_threat->RemoveBullet(jj);
								break;
							}
						}
					}

					SDL_Rect rect_threat = p_threat->GetRectFrame();
					bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
					if (bCol1 || bCol2)
					{
						int width_exp_frame = exp_main.get_frame_width_();
						int hight_exp_frame = exp_main.get_frame_height_();
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame * 0.5;
							int y_pos = (p_player.GetRect().y + p_player.get_frame_hight() * 0.5) - hight_exp_frame * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.Show(g_screen);
							SDL_RenderPresent(g_screen);
						}

						num_die++;
						if (num_die <= 3)
						{
							p_player.SetRect(0, 0);
							p_player.set_comeback_time(60);
							SDL_Delay(1000);
							player_power.Decrease();
							player_power.Render(g_screen);
							continue;
						}
						else
						{
							if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
							{
								p_threat->Free();
								Close();
								SDL_Quit();
								return 0;
							}
						}

					}

				}
			}

			int frame_exp_width = exp_threat.get_frame_width_();
			int frame_exp_hight = exp_threat.get_frame_height_();

			std::vector<BulletObject*>bullet_arr = p_player.get_bullet_list();

			for (int r = 0; r < bullet_arr.size(); r++)
			{
				BulletObject* p_bullet = bullet_arr.at(r);
				if (p_bullet != NULL)
				{
					for (int t = 0; t < threats_list.size(); t++)
					{
						ThreatsObject* obj_threat = threats_list.at(t);
						if (obj_threat != NULL)
						{
							SDL_Rect tRect;
							tRect.x = obj_threat->GetRect().x;
							tRect.y = obj_threat->GetRect().y;
							tRect.w = obj_threat->get_width_frame();
							tRect.h = obj_threat->get_hight_frame();

							SDL_Rect bRect = p_bullet->GetRect();

							bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
							if (bCol)
							{
								mark_value++;
								for (int ex = 0; ex <= NUM_FRAME_EXP; ex++)
								{
									int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
									int y_pos = p_bullet->GetRect().y - frame_exp_hight * 0.5;

									exp_threat.set_frame(ex);
									exp_threat.SetRect(x_pos, y_pos);
									exp_threat.Show(g_screen);
								}

								p_player.RemoveBullet(r);
								obj_threat->Free();
								threats_list.erase(threats_list.begin() + t);

							}
						}
					}
				}
			}

			std::string str_time = "Time:";
			Uint32 time_val = SDL_GetTicks() / 1000;
			Uint32 val_time = 300 - time_val;

			if (val_time <= 0)
			{
				if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
				{
					is_quit = true;
					break;
				}
			}
			else
			{
				std::string str_val = std::to_string(val_time);
				str_time += str_val;

				time_game.SetText(str_time);
				time_game.LoadFromRenderText(font_time, g_screen);
				time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
			}

			std::string val_str_mark = std::to_string(mark_value);
			std::string strMark("Mark:");
			strMark += val_str_mark;


			mark_game.SetText(strMark);
			mark_game.LoadFromRenderText(font_time, g_screen);
			mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 15);


			int money_cound = p_player.GetMoneyCount();
			std::string money_str = std::to_string(money_cound);

			money_count.SetText(money_str);
			money_count.LoadFromRenderText(font_time, g_screen);
			money_count.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 15);

			int val = MAX_MAP_X * TILE_SIZE - (map_data.start_x_ + p_player.GetRect().x);
			if (val <= SCREEN_WIDTH)
			{
				bossObject.SetMapXY(map_data.start_x_, map_data.start_y_);
				bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HIGHT);
				bossObject.DoPlayer(map_data);
				bossObject.Show(g_screen);
			}


			SDL_RenderPresent(g_screen);

			int real_imp_time = fps_timer.get_ticks();
			int time_one_frame = 1000 / FRAME_PER_SECOND;

			if (real_imp_time < time_one_frame)
			{
				int delay_time = time_one_frame - real_imp_time;
				if (delay_time >= 0)

					SDL_Delay(delay_time);
			}

			if (p_player.GetXpos() >= game_map.GetMaxx(map_data) - 64)
				if (MessageBox(NULL, L"VICTORY", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
			{
				Close();
				SDL_Quit();
				return 0;

			}


		
	}
		for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatsObject* p_threats = threats_list.at(i);
			if (p_threats)
			{
				p_threats->Free();
				p_threats = NULL;
			}

		}

		threats_list.clear();


		Close();
		return 0;
		
}



	