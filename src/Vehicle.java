public abstract class Vehicle {

    private  String name;
    private  double maxSpeed;
    private  double acceleration;
    private  double handling;

    private double speed;
    private double heading; // degrees, 0..360
    private double x;
    private double y;

    private double boostTimer;
    private double slipTimer;
    private double boostMultiplier = 1.0; // extra field: the diagram only stores the timer

    protected Vehicle(String name, double maxSpeed, double acceleration, double handling) {
        this.name = name;
        this.maxSpeed = maxSpeed;
        this.acceleration = acceleration;
        this.handling = handling;
    }

    public String getName() {
        return name;
    }

    public double getMaxSpeed() {
        return maxSpeed;
    }

    public double getAcceleration() {
        return acceleration;
    }

    public double getHandling() {
        return handling;
    }

    public double getSpeed() {
        return speed;
    }

    public double getHeading() {
        return heading;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getBoostTimer() {
        return boostTimer;
    }

    public double getSlipTimer() {
        return slipTimer;
    }

    // ---------- Getters / setters ----------
    public double getBoostMultiplier() {
        return boostMultiplier;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setMaxSpeed(double maxSpeed) {
        this.maxSpeed = maxSpeed;
    }

    public void setAcceleration(double acceleration) {
        this.acceleration = acceleration;
    }

    public void setHandling(double handling) {
        this.handling = handling;
    }

    public void setSpeed(double speed) {
        this.speed = speed;
    }

    public void setHeading(double heading) {
        this.heading = heading;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public void setBoostTimer(double boostTimer) {
        this.boostTimer = boostTimer;
    }

    public void setSlipTimer(double slipTimer) {
        this.slipTimer = slipTimer;
    }

    public void setBoostMultiplier(double boostMultiplier) {
        this.boostMultiplier = boostMultiplier;
    }

    public void setPosition(double x, double y) {
        this.x = x;
        this.y = y;
    }

    // ---------- Driving ----------
    public void accelerate(double dt) {
        double limit = maxSpeed * (boostTimer > 0 ? boostMultiplier : 1.0);
        speed = Math.min(speed + acceleration * dt, limit);
    }

    public void brake(double dt) {
        speed = Math.max(0, speed - acceleration * 2 * dt);
    }

    public void steerLeft(double dt) {
        steer(-dt);
    }

    public void steerRight(double dt) {
        steer(dt);
    }

    private void steer(double signedDt) {
        double grip = slipTimer > 0 ? 0.3 : 1.0; // slipping = less control
        heading += handling * grip * signedDt;
        heading = ((heading % 360) + 360) % 360;
    }

    public void move(double dt) {
        double rad = Math.toRadians(heading);
        x += Math.cos(rad) * speed * dt;
        y += Math.sin(rad) * speed * dt;
    }

    // ---------- Effects ----------
    public void applyBoost(double multiplier, double duration) {
        this.boostMultiplier = multiplier;
        this.boostTimer = duration;
    }

    public void applySlip(double duration) {
        this.slipTimer = duration;
    }

    public void updateEffects(double dt) {
        if (boostTimer > 0) {
            boostTimer = Math.max(0, boostTimer - dt);
            if (boostTimer == 0) {
                boostMultiplier = 1.0;
                speed = Math.min(speed, maxSpeed);
            }
        }
        if (slipTimer > 0) {
            slipTimer = Math.max(0, slipTimer - dt);
        }
    }

    // ---------- Abstract behaviour ----------
    public abstract void onCollision();

    public abstract String getSpecialEffect();

    @Override
    public String toString() {
        return String.format("%s [speed=%.1f, heading=%.1f, pos=(%.1f, %.1f)]",
                name, speed, heading, x, y);
    }
}
