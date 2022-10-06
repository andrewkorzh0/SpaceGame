#include "Player.h"
#include "Enemy.h"
#include "Other.h"
#include "Sound.h"

int main()
{

    //Defining
    Player player(window_size_x / 2 - 56, 590);
    SoundManager soundManager;
    soundManager.soundtrack.play();
    RectangleShape background;
    background.setSize(Vector2f(1280, 720));
    background.setFillColor(Color(27, 36, 71));
    Font debug_font;
    debug_font.loadFromFile("Assets/Fonts/pixelFont.ttf");


    //Scene Defining
    Enemy enemies[10];
    vector<Bullet> bullets(50);
    SuperBullet superBullet;
    vector<Star> stars(100);
    vector<Heart> hearts(player.health);
    for (int i = 0; i < player.health; i++)
    {
        hearts[i].setPosition(
            window_size_x - (hearts[i].sprite.getLocalBounds().width * hearts[i].sprite.getScale().x + 10) * (i + 1),
            10);
    }

    //Others
    bool DebugMode = false;
    bool DebugModeButtonIsPressed = false;

    //Window Setup
    RenderWindow main_window(VideoMode(window_size_x, window_size_y), "The Game!");
    main_window.setFramerateLimit(60);

    //Menu
    while(!inGame)
    {
        //Event Handler
        Event main_event;
        while (main_window.pollEvent(main_event))
        {
            if (main_event.type == Event::Closed)
            {
                main_window.close();
            }
        }
        main_window.clear();
        main_window.draw(background);

        Text TitleText = Text("SPACE SAGA", debug_font, 56);
        TitleText.setPosition(
            window_size_x / 2 - TitleText.getLocalBounds().width / 2,
            (window_size_y / 2 - TitleText.getLocalBounds().height / 2) - 100 );
        main_window.draw(TitleText);

        Text MenuText = Text("Press Enter to Play", debug_font, 56);
        MenuText.setPosition(
            window_size_x / 2 - MenuText.getLocalBounds().width / 2,
            (window_size_y / 2 - MenuText.getLocalBounds().height / 2) + 100);
        main_window.draw(MenuText);

        Text ControlsText = Text("Controls: arrows z x", debug_font, 36);
        ControlsText.setPosition(
            window_size_x / 2 - ControlsText.getLocalBounds().width / 2,
            (window_size_y / 2 - ControlsText.getLocalBounds().height / 2) + 150);
        main_window.draw(ControlsText);

        if (Keyboard::isKeyPressed(Keyboard::Enter))
            inGame = true;

        main_window.display();
    }


    //Gameplay
    while (player.health > 0)
    {
        //Event Handler
        Event main_event;
        while (main_window.pollEvent(main_event))
        {
            if (main_event.type == Event::Closed)
            {
                main_window.close();
            }
        }

        //Updates
        //CounterUpdates - Animations, SpawnRate
        if (frame_counter == 60)
            frame_counter = 0;
        else frame_counter += 1;

        if (spawn_counter >= spawn_rate)
            spawn_counter = 0;
        else spawn_counter += 1;


        //Spawning
        if (spawn_counter == spawn_rate && !enemies[enemies_array_counter].isActive)
        {
            double random_location = (rand() % (1280 - (int)enemy_width) + enemy_width / 2);
            enemies[enemies_array_counter].Restart(random_location);
            if (enemies_array_counter == enemies_size - 1)
                enemies_array_counter = 0;
            else enemies_array_counter += 1;
        }

        //Instanses Updates
        player.Update();
        if (Keyboard::isKeyPressed(Keyboard::Z))//Firing a bullet
        {
            if (can_fire)
            {
                if (bullet_array_counter == bullets.size() - 1)
                    bullet_array_counter = 0;
                else bullet_array_counter += 1;
                bullets[bullet_array_counter].Restart(player.x + (player.width / 2 - 10), player.y);
                can_fire = false;
                soundManager.pewpew.play();
            }
        }
        else can_fire = true;
        
        if (Keyboard::isKeyPressed(Keyboard::X))
        {
            if(player.super_blast_charge == 100)
            {
                superBullet.Restart(player.x + player.width/2 - superBullet.width/2, player.y);
                soundManager.super_pewpew.play();
                player.super_blast_charge = 0;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            if (!DebugModeButtonIsPressed)
            {
                DebugMode = !DebugMode;
                DebugModeButtonIsPressed = true;
            }
        }
        else DebugModeButtonIsPressed = false;

        for (int i = 0; i < enemies_size; i++)
        {
            if (enemies[i].isActive)
                enemies[i].Update();
        }

        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i].isActive)
                bullets[i].Update();
        }

        for (int i = 0; i < stars.size(); i++)
        {
            stars[i].Update();
        }
        superBullet.Update();

        //Collisions
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i].isActive)
            {
                for (int j = 0; j < enemies_size; j++)
                {
                    if (enemies[j].isActive)
                    {
                        if (bullets[i].x > enemies[j].x - enemy_width &&
                            bullets[i].x <= enemies[j].x + enemy_width &&
                            bullets[i].y > enemies[j].y - enemy_height &&
                            bullets[i].y <= enemies[j].y + enemy_height)
                        {
                            bullets[i].isActive = false;
                            enemies[j].isActive = false;
                            soundManager.hit.play();
                            player.score += 10;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < enemies_size; i++)
        {
            if (enemies[i].isActive && superBullet.isActive)
            {
                //100, 100 // 200, 200
                if (superBullet.x + superBullet.width > enemies[i].x - enemy_width &&
                    superBullet.x <= enemies[i].x + enemy_width &&
                    superBullet.y > enemies[i].y - enemy_height &&
                    superBullet.y <= enemies[i].y + enemy_height)
                {
                    soundManager.hit.play();
                    enemies[i].isActive = false;
                    player.score += 10;
                }
            }
        }
        for (int i = 0; i < enemies_size; i++)
        {
            if (enemies[i].isActive)
            {
                if (player.x > enemies[i].x - enemy_width &&
                    player.x <= enemies[i].x + enemy_width &&
                    player.y > enemies[i].y - enemy_height &&
                    player.y <= enemies[i].y + enemy_height)
                {
                    soundManager.hit.play();
                    player.health -= 1;
                    hearts[player.health].isActive = false;
                    enemies[i].isActive = false;
                }
            }
        }

        //Drawing
        main_window.clear();

        //Drawing Background
        main_window.draw(background, RenderStates::Default);

        //Drawing Stars
        for (int i = 0; i < stars.size(); i++)
        {
            main_window.draw(stars[i].sprite, RenderStates::Default);
        }


        //Drawing Characters
        main_window.draw(player.sprite, RenderStates::Default);


        for (int i = 0; i < 10; i++)
        {
            if (enemies[i].isActive)
                main_window.draw(enemies[i].sprite, RenderStates::Default);
        }

        //Drawing Bullets
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i].isActive)
                main_window.draw(bullets[i].sprite, RenderStates::Default);
        }

        if(superBullet.isActive)
            main_window.draw(superBullet.sprite, RenderStates::Default);

        //Drawing UI
        for(int i = 0; i < hearts.size(); i++)
        {
            if(hearts[i].isActive)
                main_window.draw(hearts[i].sprite, RenderStates::Default);
        }

        //Score Text
        Text score_text("Score is: " + to_string(player.score), debug_font, 36);
        score_text.setPosition(
            window_size_x - score_text.getLocalBounds().width - 10,//window_size_x - score_text.getLocalBounds().width - 10,
            20 + hearts[0].sprite.getLocalBounds().height * hearts[0].sprite.getScale().y);
        main_window.draw(score_text);

        //SBC Text
        Text super_blast_text("Super Blast Charge: " + to_string((int)player.super_blast_charge), debug_font, 36);
        super_blast_text.setPosition(
            window_size_x - super_blast_text.getLocalBounds().width - 10,//window_size_x - score_text.getLocalBounds().width - 10,
            40 + score_text.getLocalBounds().height + hearts[0].sprite.getLocalBounds().height * hearts[0].sprite.getScale().y);
        if (player.super_blast_charge == 100)
            super_blast_text.setFillColor(Color::Blue);
        else super_blast_text.setFillColor(Color::White);
        main_window.draw(super_blast_text);

        //Drawing debug
        if(DebugMode)
        {
            string debug_string = "Debug\nPosition X: " + to_string(player.x) + " Y: " + to_string(player.y)
                + "\nSize X: " + to_string(player.width) + " Y: " + to_string(player.height) + "\nbullets:" + to_string(bullet_array_counter)
                + " spawn cn: " + to_string(enemies_array_counter) + " Health: " + to_string(player.health) + " Score: " + to_string(player.score)
                + "\nSuper Blast Charge: " + to_string((int)player.super_blast_charge)+ " SB Pos: " + to_string(superBullet.x) + " " + to_string(superBullet.y);
            main_window.draw(Text(
                debug_string,
                debug_font,
                18));
        }
        main_window.display();
    }

    while (main_window.isOpen())
    {
        soundManager.soundtrack.stop();
        //Event Handler
        Event main_event;
        while (main_window.pollEvent(main_event))
        {
            if (main_event.type == Event::Closed)
            {
                main_window.close();
            }
        }
        main_window.clear();
        main_window.draw(background);
        Text GameOverText = Text("Game Over!", debug_font, 56);
        GameOverText.setPosition(
            window_size_x / 2 - GameOverText.getLocalBounds().width/2,
            window_size_y / 2 - GameOverText.getLocalBounds().height/2);
        main_window.draw(GameOverText);
        main_window.display();
    }
}
