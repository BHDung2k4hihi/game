
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include"BaseObject.h"
#include"CommonFunc.h"

class BulletObject : public BaseObject
{
public:
	BulletObject();
	~BulletObject();

	enum BulletDir
	{
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
		DIR_UP = 22,
		DIR_UP_RIGHT = 23,
		DIR_UP_LEFT = 24,
		DIR_DOWN_RIGHT = 25,
		DIR_DOWN_LEFT = 26,
		DIR_DOWN = 27,
		
	};

	enum BulletType
	{
		SPHERE_BULLET = 50,
		LASER_BULLET = 51,
	};

	void set_x_val(const int& xVal) { x_val_ = xVal; }
	void set_y_val(const int& yVal) { y_val_ = yVal; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }
	int get_rect_x() const { return rect_.x; }
	int get_rect_y() const { return rect_.y; }

	void set_type_bullet(const int& typeBullet) { type_bullet_ = typeBullet; }
	int get_type_bullet() const { return type_bullet_; }

	void SetDireCtion(const int& xVal, const int& yVal);
	void SetDireCtion1(const SDL_Rect* target_position);

	void set_is_move(const bool& isMove) { is_move_ = isMove; }
	bool get_is_move() const { return is_move_; }

	void CheckToMap(Map& map_data);

	void set_bullet_dir(const unsigned int& bulletDir) { bullet_dir_ = bulletDir; }
	unsigned int get_bullet_dir() const { return bullet_dir_; }

	void set_bullet_type(const unsigned int& bulletType) { bullet_type_ = bulletType; }
	unsigned int get_bullet_type() const { return bullet_type_; }

	void HandleMove(const int& x_border, const int& y_border);
	//void HandleMove1(const int& x_bprder, const int& y_border);
	bool LoadImgBullet(SDL_Renderer* des);
	/*void Show(SDL_Renderer* renderere);
	virtual bool LoadImg1(std::string path, SDL_Renderer* screen);*/

private:
	int x_val_;
	int y_val_;
	float x_pos_;
	float y_pos_;
	int initial_x_val_;
	int initial_y_val_;
	bool is_move_;
	unsigned int bullet_dir_;
	unsigned int bullet_type_;

	int type_bullet_;
	double angle_of_bullet_;
};


#endif // !BULLET_OBJECT_H_
