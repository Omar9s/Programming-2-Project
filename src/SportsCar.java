public class SportsCar extends Vehicle {

    public SportsCar() {
        super("Sports Car", 220, 80, 120);
    }

    @Override
    public void onCollision() {
        // Fast but fragile: loses a lot of speed
        setSpeed(getSpeed() * 0.5);
    }

    @Override
    public String getSpecialEffect() {
        return "Nitro Boost: x1.5 speed for 3s";
    }
}
