public class Bike extends Vehicle {

    public Bike() {
        super("Bike", 180, 65, 160);
    }

    @Override
    public void onCollision() {
        // Light: loses most of its speed and slips
        setSpeed(getSpeed() * 0.3);
        applySlip(1.5);
    }

    @Override
    public String getSpecialEffect() {
        return "Agile Handling: sharp turns, but slips after a crash";
    }
}
