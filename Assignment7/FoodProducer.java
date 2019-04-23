
import FoodBank;

public class FoodProducer extends Thread {
  
  FoodBank bank;

  public FoodProducer(FoodBank bank) {
    this.bank = bank; 
  }

  public void run() {
    int amount;
    while (true) {

      amount = random.random();

      bank.giveFood(amount);

      Thread.sleep(100);
    }
  }

}
