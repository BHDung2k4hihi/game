#include"stdafx.h"
#include"CommonFunc.h"
#include"BulletObject.h"

BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	bullet_type_ = SPHERE_BULLET;
}

BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	bool ret = false;
	if (bullet_type_ == LASER_BULLET)
	{
		 ret = LoadImg("player_bullet.png", des);
	}
	else
	{
		ret = LoadImg("da_bullet.png", des);
	}

	return ret;
	
}

//bool BulletObject::LoadImg1(std::string path, SDL_Renderer* screen)
//{
//	Free();
//	SDL_Texture* new_texture = NULL;
//	SDL_Surface* load_surface = IMG_Load(path.c_str());
//	if (load_surface != NULL)
//	{
//		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
//		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
//		if (new_texture != NULL)
//		{
//			rect_.w = load_surface->w;
//			rect_.h = load_surface->h;
//		}
//		SDL_FreeSurface(load_surface);
//	}
//	p_object_ = new_texture;
//
//	return p_object_ != NULL;
//
//}
//
//void BulletObject::Show(SDL_Renderer* renderer)
//{
//	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
//	SDL_RenderCopyEx(renderer, p_object_, NULL, &renderquad, angle_of_bullet_, NULL, SDL_FLIP_NONE);
//}
//
//void BulletObject::CheckToMap(Map& map_data)
//{
//	int x = (rect_.x + map_data.start_x_) / TILE_SIZE;
//	int y = (rect_.y + map_data.start_y_) / TILE_SIZE;
//	if (x > 0 && x < MAX_MAP_X && y > 0 && y < MAX_MAP_Y)
//	{
//		if (map_data.tile[y][x] != BLANK_TILE && map_data.tile[y][x] != STATE_MONEY)
//		{
//			is_move_ = false;
//
//		}
//	}
//}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	if (bullet_dir_ == DIR_RIGHT)
	{
		rect_.x += x_val_;
		if (rect_.x > x_border)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_LEFT)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_UP)
	{
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_UP_LEFT)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_UP_RIGHT)
	{
		rect_.x += x_val_;
		if (rect_.x > x_border)
		{
			is_move_ = false;
		}
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}
	
	
}
