#include "Demo.h"


Demo::Demo()
{
}


Demo::~Demo()
{
}

void Demo::Init()
{
	text.InitText();
	text.setProgram();
	inputmanager = player.BuildPlayerSprite(GetScreenWidth(), GetScreenHeight(), inputmanager);
	pisang.BuildSprite(GetScreenWidth(), GetScreenHeight(), "banana.png", 0.2f);
	pisang2.BuildSprite(GetScreenWidth(), GetScreenHeight(), "banana.png", 0.2f);
	pisang3.BuildSprite(GetScreenWidth(), GetScreenHeight(), "banana.png", 0.2f);
	cherry.BuildSprite(GetScreenWidth(), GetScreenHeight(), "cherry.png", 0.3f);
	cherry2.BuildSprite(GetScreenWidth(), GetScreenHeight(), "cherry.png", 0.3f);
	orange.BuildSprite(GetScreenWidth(), GetScreenHeight(), "orange.png", 0.4f);
	bomb.BuildSprite(GetScreenWidth(), GetScreenHeight(), "bomb.png", 0.1f);
	bomb2.BuildSprite(GetScreenWidth(), GetScreenHeight(), "bomb.png", 0.1f);
	bomb3.BuildSprite(GetScreenWidth(), GetScreenHeight(), "bomb.png", 0.1f);
	bg.BuildBackground(GetScreenWidth(), GetScreenHeight(),"bg_play.png");
	hati1.BuildHeart(GetScreenWidth(), GetScreenHeight(), "fill.png", 0);
	hati2.BuildHeart(GetScreenWidth(), GetScreenHeight(), "fill.png", 56);
	hati3.BuildHeart(GetScreenWidth(), GetScreenHeight(), "fill.png", 112);
	hatikosong1.BuildHeart(GetScreenWidth(), GetScreenHeight(), "empty.png", 0);
	hatikosong2.BuildHeart(GetScreenWidth(), GetScreenHeight(), "empty.png", 56);
	hatikosong3.BuildHeart(GetScreenWidth(), GetScreenHeight(), "empty.png", 112);
	audio.InitAudio();
	
	//BuildPlayerSprite();
}

void Demo::Update(float deltaTime)
{
	audio.PlayAudio();
	if (lives == 0)
	{
		SDL_Quit();
		state = State::EXIT;
		cek = false;
		//Engine::Game &game = Menu();
		//game.Start("User Interface Menu", 800, 600, false, WindowFlag::WINDOWED, 60, 1);
		//exit(0);
	}

	if (inputmanager.IsKeyDown("Quit")) {
		SDL_Quit();
		exit(0);
	}
	player.UpdateSpriteAnim(deltaTime);
	player.ControlPlayerSprite(deltaTime,inputmanager, GetScreenWidth());


	pisang.setYpost(pisang.getYpos() + deltaTime * pisang.getXVelocity());
	pisang2.setYpost(pisang2.getYpos() + deltaTime * pisang2.getXVelocity());
	pisang3.setYpost(pisang3.getYpos() + deltaTime * pisang3.getXVelocity());
	cherry.setYpost(cherry.getYpos() + deltaTime * cherry.getXVelocity());
	cherry2.setYpost(cherry2.getYpos() + deltaTime * cherry2.getXVelocity());
	orange.setYpost(orange.getYpos() + deltaTime * orange.getXVelocity());
	bomb.setYpost(bomb.getYpos() + deltaTime * bomb.getXVelocity());
	if (score > 500)
	{
		bomb2.setYpost(bomb2.getYpos() + deltaTime * bomb2.getXVelocity());
	}
	if (score > 1000)
	{
		bomb3.setYpost(bomb3.getYpos() + deltaTime * bomb3.getXVelocity());
	}
	
	static int frameCounter = 0;
	frameCounter++;
	if (frameCounter == 180) {
		if (bomb.getXVelocity() == 0.6f || bomb2.getXVelocity() == 0.6f || bomb3.getXVelocity() == 0.6f)
		{
		}
		else {
			bomb.setXVelocity(bomb.getXVelocity() + 0.01f);
		}
		if (score > 500 && bomb2.getXVelocity() != 0.6f)
		{
			bomb2.setXVelocity(bomb2.getXVelocity() + 0.01f);
		}
		if (score > 1000 && bomb3.getXVelocity() != 0.6f)
		{
			bomb3.setXVelocity(bomb3.getXVelocity() + 0.01f);
		}
		frameCounter = 0;
	}

	//pisang
	if (pisang.getYpos() >= GetScreenHeight()) {
		pisang.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		pisang.setXpost((float)random_integer);
	}
	if (pisang2.getYpos() >= GetScreenHeight()) {
		pisang2.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		pisang2.setXpost((float)random_integer);
	}
	if (pisang3.getYpos() >= GetScreenHeight()) {
		pisang3.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		pisang3.setXpost((float)random_integer);
	}



	//cherry
	if (cherry.getYpos() >= GetScreenHeight()) {
		cherry.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		cherry.setXpost((float)random_integer);
	}
	if (cherry2.getYpos() >= GetScreenHeight()) {
		cherry2.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		cherry2.setXpost((float)random_integer);
	}


	//orange
	if (orange.getYpos() >= GetScreenHeight()) {
		orange.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		orange.setXpost((float)random_integer);
	}

	//bomb 1 2 3
	if (bomb.getYpos() >= GetScreenHeight()) {
		bomb.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		bomb.setXpost((float)random_integer);
	}
	if (bomb2.getYpos() >= GetScreenHeight()) {
		bomb2.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		bomb2.setXpost((float)random_integer);
	}
	if (bomb3.getYpos() >= GetScreenHeight()) {
		bomb3.setYpost(0);

		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % 8) * 100;
		}
		bomb3.setXpost((float)random_integer);
	}

	//kalau tabrakan
	//pisang 1 2 3
	if (isCollided(player, pisang))
	{
		pisang.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		pisang.setXpost(random_integer);
		score += 10;
	}
	if (isCollided(player, pisang2))
	{
		pisang2.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		pisang2.setXpost(random_integer);
		score += 10;
	}
	if (isCollided(player, pisang3))
	{
		pisang3.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		pisang3.setXpost(random_integer);
		score += 10;
	}
	//cherry 1 2
	if (isCollided(player, cherry))
	{
		cherry.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		cherry.setXpost(random_integer);
		score += 20;
	}
	if (isCollided(player, cherry2))
	{
		cherry2.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		cherry2.setXpost(random_integer);
		score += 20;
	}
	//orange
	if (isCollided(player, orange))
	{
		orange.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		orange.setXpost(random_integer);
		score += 20;
	}
	//bomb
	if (isCollided(player, bomb))
	{
		bomb.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		bomb.setXpost(random_integer);

		lives -= 1;
	}
	if (isCollided(player, bomb2))
	{
		bomb2.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		bomb2.setXpost(random_integer);

		lives -= 1;
	}
	if (isCollided(player, bomb3))
	{
		bomb3.setYpost(0);
		int random_integer;
		for (int index = 0; index < 1; index++) {
			random_integer = (rand() % GetScreenWidth() / 100) * 100;
		}
		bomb3.setXpost(random_integer);

		lives -= 1;
	}
	if (lives == 2) {hati3.setVisibility(false);}	
	if (lives == 1) {hati2.setVisibility(false);}
	if (lives == 0) {hati1.setVisibility(false);}
	hasilscore = to_string(score);
}

void Demo::Render()
{
	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	


	bg.DrawBackground();
	text.RenderText("Score = " + hasilscore , 0, 60, 0.8f, vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f), GetScreenWidth(), GetScreenHeight());
	player.DrawPlayerSprite();
	pisang.DrawSprite();
	pisang2.DrawSprite();
	pisang3.DrawSprite();
	cherry.DrawSprite();
	cherry2.DrawSprite();
	orange.DrawSprite();
	bomb.DrawSprite();
	if (score > 500)
	{
		bomb2.DrawSprite();
	}if (score > 1000)
	{
		bomb3.DrawSprite();
	}

	hatikosong1.DrawHeart();
	hatikosong2.DrawHeart();
	hatikosong3.DrawHeart();

	if (hati1.getVisibility())
	{
		hati1.DrawHeart();
	}	
	if (hati2.getVisibility())
	{
		hati2.DrawHeart();
	}	
	if (hati3.getVisibility())
	{
		hati3.DrawHeart();
	}
	

	
	
}

bool Demo::isCollided(Player a, Fruit b) {

	return(a.getXpos() < b.getXpos() + b.getFrameWidth() && a.getXpos() + a.getFrameWidth() > b.getXpos() && a.getYpos() < b.getYpos() + b.getFrameHeight() && b.getYpos() + a.getFrameHeight() > b.getYpos());

}





void Demo::play() {


	//return 0;
}


