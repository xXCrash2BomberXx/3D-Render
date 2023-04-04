package App;

import java.awt.Color;
import App.Control.Control;
import App.Model.J3D;
import App.Model.JObject;
import App.Model.Sprite;

public class App {
    public static void main(String args[]) throws IllegalArgumentException {
        JObject object1_1 = new JObject("cube", 200, 200, 0, 50, 50, 50, false, true);  // No Fill, Auto Outline
        JObject object1_2 = new JObject("cube", 200, 200, 50, 50, 50, 50, 225, 225, 25, 
                                        new Color[] { Color.BLUE }, new Color[] { Color.RED });  // Blue Fill, Red Outline
        JObject object1_4 = new JObject("icosahedron", 200, 200, 0, 50, 50, 50, false, 
                                        new Color[]{});  // No Fill, Black Outline
        JObject object1_3 = new JObject("cube", 150, 200, 0, 50, 50, 50, 225, 225, 25, 
                                        true, false);  // Auto Fill, No Outline
        JObject object2 = new JObject("icosahedron", 25, 25, 0, 50, 50, 50, 
                                        new Color[]{}, false);  // Black Fill, No Outline
        JObject object3 = new JObject("dodecahedron", 400, 400, 0, 50, 50, 50, 
                                        true);  // Auto Fill, No Outline
        JObject object4 = new JObject("octahedron", 25, 400, 0, 50, 50, 50, 
                                        new Color[] { Color.BLUE, Color.RED });  // Alternating Blue and Red Fill, No Outline
        JObject object5 = new JObject("tetrahedron", 225, 400, 0, 50, 50, 50);  // Atuo Fill, No Outline

        // NOTE: Sprites render on one Container, ignore depth, cannot be colored by face, and always appear on top but are faster to render
            // All the mentioned limitations except the coloring by face can be overcome through usage of seperate Containers
            // This is due to the Sprite being rendered as a single path instead of individual fillable paths
        Sprite sprite1 = new Sprite("tetrahedron", 400, 25, 0, 50, 50, 50);
        Sprite sprite2 = new Sprite("icosahedron", 225, 25, 0, 50, 50, 50);
        if (args.length > 0) {
            int width;
            try {
                width = Integer.parseInt(args[0].split(",")[0]);
            } catch (NumberFormatException e) {
                throw new IllegalArgumentException("Exected a numeric width parameter");
            }
            int height;
            try {
                height = Integer.parseInt(args[0].split(",")[1]);
            } catch (ArrayIndexOutOfBoundsException e) {
                throw new IllegalArgumentException("Expected a height paramter");
            } catch (NumberFormatException e) {
                throw new IllegalArgumentException("Exected a numeric height parameter");
            }
            new Control(new J3D[] { object1_1, object1_2, object1_3, object1_4,
                                object2, object3, object4, object5,
                                sprite1, sprite2 },
                                width, height);
        } else {
            new Control(new J3D[] { object1_1, object1_2, object1_3, object1_4,
                                object2, object3, object4, object5,
                                sprite1, sprite2 });
        }
    }
}
