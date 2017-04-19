/*   END asteroid.h   */

#include "asteroid.h"
#include "main.h"

// makes pseudo random asteroid and adds to belt
void makeAsteroid(){

}
void makeMakeMultAsteroid(unsigned int n){
  while(n){
    makeAsteroid();
    n--;
  }
}
void addAsteroid(struct Asteroid a){

}
void drawAsteroid(struct Asteroid *a){

}
void drawAllAsteroids(){
  struct AsteroidBelt *curr = &ASTEROIDS;
  while((curr->curr) != NULL){
    drawAsteroid(curr->curr);
    curr = curr->next;
  }
}



/*   END asteroid.c   */
