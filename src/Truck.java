public class Truck extends Vehicle {

    public Truck() {
        super("Truck", 140, 35, 60);
    }

    @Override
    public void onCollision() {
        // Heavy: barely slowed down by a hit
        setSpeed(getSpeed() * 0.9);
    }

    @Override
    public String getSpecialEffect() {
        return "Heavy Armor: minimal speed loss on collision";
    }
}
