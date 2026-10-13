import 'dart:io';
import 'dart:math';

void main() {
  final human = Human("a", 1);
  print(human.name);
  final Human(:name, :age) = human;
  print(human.age);

}

class Human{
  String name;
  int age;
  Human(this.name,this.age);
}
