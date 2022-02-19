# sdl4cpp
## sdl4cpp, header-only C++ wrapper around SDL2 (heavily work-in-progress)

### An example:

```cpp
#include "sdl4cpp/sdl4.hpp"
#include "sdl4cpp/timer.hpp"
#include "sdl4cpp/video.hpp"

int main() noexcept {
    sdl4::video::window::window wnd;
    sdl4::video::window::renderer::renderer render;

    if(sdl4::init(SDL_INIT_VIDEO) != 0) { return 1; }

    if(wnd.create_window_and_renderer(600, 400, 0, &render) == 0) {
        render.set_render_draw_color(155, 155, 13, SDL_ALPHA_OPAQUE);
        render.render_draw_line(350, 200, 300, 240);
        render.set_render_draw_color(200, 105, 55, SDL_ALPHA_OPAQUE);
        render.render_draw_line(0, 10, 600, 10);
        render.render_present();
        sdl4::timer::delay(3500);
    }

    sdl4::quit();
}
```
 
### sdl4cpp licensed under the terms of MIT License.
