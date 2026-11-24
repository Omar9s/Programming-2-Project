/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author ziadhindawy
 */
public class Obstacle extends TrackObject{

    public Obstacle(double x, double y, double width, double height) {
        super(x, y, width, height);
    }
    
    public void applyEffect(Vehicle v){
        v.onCollision(); // tbata2 aw tefked ta7akom 7asab no3ha sport wala truck
        deactivate(); //   active = false w lazem te5fy el obstacle 
    }
    
    
    @Override
    public String getKind(){
        return "OBSTACLE";
    }
}
