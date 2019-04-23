
public class FoodBank {
  
  int food;

  public FoodBank() {
    food = 0; 
  }

  public int takeFood(int amount) {
    food -= amount; 
  }

  public int giveFood(int amount) {
    food += amount; 
  }
}
