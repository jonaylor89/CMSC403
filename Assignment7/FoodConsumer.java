
import FoodBank;

public class FoodConsumer extends Thread {

  FoodBank bank;

  public FoodConsumer(FoodBank bank) {
    this.bank = bank; 
  }

  public void run() {
    int amount;
    while (true) {
      amount = random.random();

      bank.takeFood(amount);

      Thread.sleep(100);
    }
  }

}
