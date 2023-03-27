package App;

import App.Control.Control;
import App.View.J3D;
import App.View.JObject;
import App.View.Sprite;

public class App {
    public static void main(String args[]) throws IllegalArgumentException {
        // NOTE: Sprites render on one Container, ignore depth, cannot be colored by face, and always appear on top but are faster to render
        JObject sprite1_1 = new JObject("cube", 200, 200, 0, 50, 50, 50);
        JObject sprite1_2 = new JObject("cube", 200, 200, 50, 50, 50, 50, 225, 225, 25);
        JObject sprite1_3 = new JObject("cube", 150, 200, 0, 50, 50, 50, 225, 225, 25);
        JObject sprite2 = new JObject("icosahedron", 25, 25, 0, 50, 50, 50);
        JObject sprite3 = new JObject("dodecahedron", 425, 400, 0, 50, 50, 50);
        JObject sprite4 = new JObject("octahedron", 25, 400, 0, 50, 50, 50, true);
        Sprite sprite5 = new Sprite("tetrahedron", 425, 25, 0, 50, 50, 50);
        Sprite sprite6 = new Sprite("icosahedron", 200, 200, 0, 50, 50, 50);
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
            new Control(new J3D[] { sprite1_1, sprite1_2, sprite1_3, sprite2, sprite3, sprite4, sprite5, sprite6 },
                    width, height);
        } else {
            new Control(new J3D[] { sprite1_1, sprite1_2, sprite1_3, sprite2, sprite3, sprite4, sprite5, sprite6 });
        }
    }
}
