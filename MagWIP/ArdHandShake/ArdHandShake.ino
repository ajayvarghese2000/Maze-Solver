int i=0;
void setup() 
{
  Serial.begin(9600);
  Serial.print('a');
  char a = 'b';
  while(a != 'a')
  {
    a=Serial.read();
  }
}
 
void loop() 
{

}
