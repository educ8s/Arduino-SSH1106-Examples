#include <GyverOLED.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

GyverOLED<SSH1106_128x64> screen;

class Paddle {

 protected:
 void LimitMovement()
 {
   if(y < 0)
   {
     y = 0;
   }
   if( y+ height >= screen_height)
   {
     y = screen_height - height;
   }
 } 
 public:
 int x, y;
 int width, height;
 int speed;
 int screen_height;

  void Draw(){
    screen.rect(x, y, x+width, y+height, OLED_FILL );
  }

  void Update(int ball_speed, int ball_y)
  {
    if (ball_y > y && ball_speed < 0)
    {
      y += speed;
    }
    if (ball_y < y + height && ball_speed < 0)
    {
      y -= speed;
    }
    LimitMovement();

  }
};

class RightPaddle :public Paddle{
  public:
  void Update(int ball_speed, int ball_y)
  {
    if (ball_y > y  && ball_speed > 0)
    {
      y += speed;
    }
    if (ball_y < y + height && ball_speed > 0)
    {
      y -= speed;
    }
    LimitMovement();
  }
};

class Ball{
  public:
  int x, y;
  int radius;
  int speed_x;
  int speed_y;

  void Draw(){
    screen.circle(x, y, radius, 1);
  }

  void Update(Paddle &player, Paddle &cpu) {
    x += speed_x;
    y += speed_y;

    if (y + radius >= SCREEN_HEIGHT - 1)
    {
        speed_y *= -1;
        y = SCREEN_HEIGHT - 1 - radius;
    }
    
    if( y - radius <= 1) {
      speed_y *= -1;
    }

    if (x + radius >= SCREEN_WIDTH - 1){
        ResetBall();
    }
    
    if( x - radius <= 1){
      ResetBall();
    }

    if ((x - radius <= cpu.x + cpu.width) && (y + radius > cpu.y) && (y-radius < cpu.y + cpu.height))
    {
      speed_x *= -1;
    }

     if ((x + radius >= player.x) && (y + radius > player.y) && (y-radius < player.y + player.height))
    {
      speed_x *= -1;
    }
  }

  void ResetBall()
  {
    x = SCREEN_WIDTH/2;
    y = SCREEN_HEIGHT/2;
  }
};

Ball ball;
Paddle cpu;
RightPaddle player;

void setup(void) {
  initDisplay();
  Wire.setClock(800000L);

  ball.x = SCREEN_WIDTH/2;
  ball.y = SCREEN_HEIGHT/2;
  ball.radius = 3;
  ball.speed_x = 2;
  ball.speed_y = 2;

  screen.clear();

  cpu.width = 4;
  cpu.height = 18;
  cpu.x = 3;
  cpu.y = (SCREEN_HEIGHT-1)/2 - cpu.height/2;
  cpu.speed = 4;
  cpu.screen_height = SCREEN_HEIGHT;

  player.width = 4;
  player.height = 18;
  player.x = (SCREEN_WIDTH-1) - player.width - 3;
  player.y = (SCREEN_HEIGHT-1)/2 - player.height/2;
  player.speed = 4;
  player.screen_height = SCREEN_HEIGHT;
}

void loop() {
  
  screen.clear();
  //screen.fastLineV(SCREEN_WIDTH/2, 0, SCREEN_HEIGHT, 1);
  ball.Update(player, cpu);
  cpu.Update(ball.speed_x, ball.y);
  player.Update(ball.speed_x, ball.y);
  ball.Draw();
  player.Draw();
  cpu.Draw();
  screen.update();
}

void initDisplay()
{
  screen.init();  
  screen.clear();   
  screen.update(); 
}