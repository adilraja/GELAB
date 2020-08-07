int _energy;
int _picked_up;

int main(){
  initGEant();
  initGEtrail();
  ReadTrailGEtrail("santafe.trl");
  //Do something with ant
  while(_energy>0){

