#include <Novice.h>
#include <time.h>

const char kWindowTitle[] = "test";

class Box {
public:
	int X[3];
	int Y[3];
	int width[3];
	int height[3];

	void upper(int x, int y, int w, int h) {
		X[0] = x;
		Y[0] = y;
		width[0] = w;
		height[0] = h;
	}

	void middle(int x, int y, int w, int h) {
		X[1] = x;
		Y[1] = y;
		width[1] = w;
		height[1] = h;
	}

	void lower(int x, int y, int w, int h) {
		X[2] = x;
		Y[2] = y;
		width[2] = w;
		height[2] = h;
	}
};


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 宣言と初期化
	float playerposx = 30;
	float playerposy = 560;
	//int isplayersurvive = 1;
	int isdash = 0;
	//int isattack = 0;
	int playerLspeed = 5;
	int playerRspeed = 5;
	int dashspeed = 10;

	float  playervelocityY = 0.0f;
	float playeracceleration = 0.8f;

	bool isPlJump = false;
	bool isHitUp = false;
	bool isHitGround = false;

	Box box;
	box.X[0];
	box.Y[0];
	box.width[0];
	box.height[0];

	box.X[1];
	box.Y[1];
	box.width[1];
	box.height[1];

	box.X[2];
	box.Y[2];
	box.width[2];
	box.height[2];


	int Player[] = {
		{Novice::LoadTexture("./Resources/Player_normal.png")},
		//{Novice::LoadTexture("./Resources/Player_normal_left.png")} 
	};

	int Block[] = {
		{Novice::LoadTexture("./Resources/ground.png")},
		{Novice::LoadTexture("./Resources/Box.png")}
	};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_A]) {
			playerposx -= playerLspeed;
		}
		if (keys[DIK_LSHIFT] && keys[DIK_A]) {
			playerposx -= dashspeed;
			isdash = 1;
			/*if (isdash == 1 && isattack == 1) {

			}*/
		}
		if (keys[DIK_D]) {
			playerposx += playerRspeed;
		}
		if (keys[DIK_LSHIFT] && keys[DIK_D]) {
			playerposx += dashspeed;
			isdash = 1;
			/*if (isdash == 1 && isattack == 1) {

			}*/
		}



		// 当たり判定
		box.upper(0, 300, 32 * 10, 32);
		box.middle(400, 400, 32 * 4, 32);
		box.lower(600, 500, 32 * 12, 32);

		if (isPlJump) {
			playervelocityY -= playeracceleration;
			playerposy -= playervelocityY;
		}

		// ブロックの下辺
		if ((int)playerposx + 64 >= box.X[1] && (int)playerposx <= box.X[1] + box.width[1]
			&& (int)playerposy <= box.Y[1] + box.height[1] && (int)playerposy >= box.Y[1]) {

			playervelocityY = 0.0f;
		}

		if ((int)playerposx + 59 >= box.X[2] && (int)playerposx + 5 <= box.X[2] + box.width[2] 
			&& (int)playerposy <= box.Y[2] + box.height[2] && (int)playerposy >= box.Y[2]) {

			playervelocityY = 0.0f;
		}

		for (int i = 0; i <= 2; i++) {
			// ブロックの上辺
			if ((int)playerposx + 64 >= box.X[i] && (int)playerposx <= box.X[i] + box.width[i] &&
				(int)playerposy + 95 >= box.Y[i] && (int)playerposy + 95 <= box.Y[i] + box.height[i]) {

				isPlJump = false;
				isHitUp = true;
				isHitGround = false;
			} else if((int)playerposy + 96 >= 656){
				isPlJump = false;
				isHitUp = false;
				isHitGround = true;
			} else {
				isHitUp = false;
				isHitGround = false;
			}

			if (isHitUp) {
				playerposy = (float)box.Y[i] - 96;
				playervelocityY = 0.0f;

				if (keys[DIK_W] && preKeys[DIK_W] == 0) {
					isHitUp = false;
					playervelocityY = 20.0f;
					isPlJump = true;
				}
			}

			if (isHitGround) {
				playerposy = 656 - 96;

				if (keys[DIK_W] && preKeys[DIK_W] == 0) {
					isHitGround = false;
					playervelocityY = 20.0f;
					isPlJump = true;
				}
			}

			if (!isHitUp && !isHitGround && !isPlJump) {
				playervelocityY = -3.0f;
				playervelocityY -= playeracceleration;
				playerposy -= playervelocityY;
			}

			// ブロックの右辺
			if ((int)playerposy + 95 >= box.Y[i] && (int)playerposy + 10 <= box.Y[i] + box.height[i] &&
				(int)playerposx <= box.X[i] + box.width[i] && (int)playerposx >= box.X[i] + (box.width[i] / 2)) {
				playerLspeed = 0;
			} else {
				playerLspeed = 5;
			}

			// ブロックの左辺
			if ((int)playerposy + 95 >= box.Y[i] && (int)playerposy + 10 <= box.Y[i] + box.height[i] &&
				(int)playerposx + 64 <= box.X[i] && (int)playerposx + 64 >= box.X[i] + (box.width[i] / 2)) {
				playerRspeed = 0;
			} else {
				playerRspeed = 5;
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::DrawSprite((int)playerposx, (int)playerposy, Player[0], 1.0f, 1.0f, 0.0f, WHITE);

		for (int i = 0; i <= 39; i++) {
			Novice::DrawSprite(0 + 32 * i, 656, Block[1], 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(0 + 32 * i, 688, Block[1], 1.0f, 1.0f, 0.0f, WHITE);
		}

		for (int i = 0; i <= 9; i++) {
			Novice::DrawSprite(box.X[0] + 32 * i, box.Y[0], Block[1], 1.0f, 1.0f, 0.0f, WHITE);
		}

		for (int i = 0; i <= 3; i++) {
			Novice::DrawSprite(box.X[1] + 32 * i, box.Y[1], Block[1], 1.0f, 1.0f, 0.0f, WHITE);
		}

		for (int i = 0; i <= 11; i++) {
			Novice::DrawSprite(box.X[2] + 32 * i, box.Y[2], Block[1], 1.0f, 1.0f, 0.0f, WHITE);
		}

		Novice::ScreenPrintf(0, 0, "%d", (int)playerposy);
		Novice::ScreenPrintf(0, 15, "%d", (int)playerposx);
		Novice::ScreenPrintf(0, 30, "%d", isHitUp);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}