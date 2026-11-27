
/**
 *
 * @author ziadhindawy
 */

import javafx.geometry.Rectangle2D;

public class TrackObject {
    private double x;
    private double y;
    private double width;
    private double height;
    private boolean active;

    public TrackObject(double x, double y, double width, double height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.active = true; // true 3ashan fi el awel kol 7aga mawgooda sawa2 obstacle,boost,oilSpill
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }

    public boolean isActive() {
        return active;
    }
    
    public void reset() {
        active = true; // lama adoos reset lazem kol 7aga teb2a mawgooda tani f true
    }
    
    protected void deactivate() {
        active = false; // lama te5bat fi obstacle lazem ye5tefy w hayeb2a false  
    }
    
    public void applyEffect(Vehicle v){
    
    }
    public String getKind(){// 3ashan a3raf no3o lama agy arsem ya3ni el obtacle masaln a7mar el boost azra2
        return "NONE";
    }
    
    public Rectangle2D getBounds() {
    return new Rectangle2D(x, y, width, height);
}
    
    
}
