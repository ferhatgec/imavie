// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef SDL4CPP_VIDEO_HPP
#define SDL4CPP_VIDEO_HPP

#include <SDL2/SDL_syswm.h>
#include "sdl4.hpp"

namespace sdl4 {
    namespace video {
        namespace display {
            template<typename DriverData>
            class mode {
            public:
                std::uint32_t format;
                int w, h, refresh_rate;
                DriverData driver_data;
            public:
                mode() = default; ~mode() = default;

                template<typename DriverType>
                SDL_DisplayMode* to(sdl4::video::display::mode<DriverType> __mode) {
                    SDL_DisplayMode* val;
                    val->format = __mode.format;
                    val->w = __mode.w; val->h = __mode.h; val->refresh_rate = __mode.refresh_rate;
                    val->driverdata = __mode.driver_data; return val;
                }

                template<typename DriverType>
                mode get_closest_dm(int dp_index,
                                    const sdl4::video::display::mode<DriverType> __mode,
                                    sdl4::video::display::mode<DriverType> closest) {
                    return this->to(SDL_GetClosestDisplayMode(dp_index, this->to(__mode), this->to(closest)));
                }

                int get_current_dm(int dp_index) {
                    return SDL_GetCurrentDisplayMode(dp_index,
                                                     this->to(sdl4::video::display::mode<DriverData> {
                                                         .format = this->format,
                                                         .w = this->w, .h = this->h, .refresh_rate = this->refresh_rate,
                                                         .driver_data = this->driver_data
                                                     }));
                }

                int get_desktop_dm(int dp_index) {
                    return SDL_GetDesktopDisplayMode(dp_index,
                                                     this->to(sdl4::video::display::mode<DriverData> {
                                                         .format = this->format,
                                                         .w = this->w, .h = this->h, .refresh_rate = this->refresh_rate,
                                                         .driver_data = this->driver_data
                                                     }));
                }

                int get_dm(int dp_index, int mode_index) {
                    return SDL_GetDisplayMode(dp_index, mode_index,
                                              this->to(sdl4::video::display::mode<DriverData>{
                                                  .format = this->format,
                                                  .w = this->w, .h = this->h, .refresh_rate = this->refresh_rate,
                                                  .driver_data = this->driver_data
                                              }));
                }
            };

            const std::string get_current_video_driver() { return sdl4::convert(SDL_GetCurrentVideoDriver()); }
            const std::string get_display_name(int dp_index) { return sdl4::convert(SDL_GetDisplayName(dp_index)); }
            const std::string get_video_driver(int index) { return sdl4::convert(SDL_GetVideoDriver(index)); }

            int get_display_dpi(int dp_index, float* ddpi, float* hdpi, float* vdpi) { return SDL_GetDisplayDPI(dp_index, ddpi, hdpi, vdpi); }
            int get_num_display_modes(int dp_index) { return SDL_GetNumDisplayModes(dp_index); }
            int get_num_video_displays() { return SDL_GetNumVideoDisplays(); }
            int get_num_video_drivers() { return SDL_GetNumVideoDrivers(); }
        }

        namespace rect {
            class rect {
            public:
                SDL_Rect* main;
            public:
                rect() = default; ~rect() = default;

                int get_display_bounds(int dp_index) {
                    return SDL_GetDisplayBounds(dp_index, this->main);
                }

                int get_display_usable_bounds(int dp_index) {
                    return SDL_GetDisplayUsableBounds(dp_index, this->main);
                }
            };
        }

        namespace window {
            namespace renderer {
                class renderer {
                public:
                    SDL_Renderer *main;
                public:
                    renderer() = default; ~renderer() { this->destroy_renderer(); };

                    void create_software_renderer(SDL_Surface* surface) {
                        this->main = SDL_CreateSoftwareRenderer(surface);
                    }

                    SDL_Texture* create_texture(std::uint32_t format, int access,
                                                int w, int h) { return SDL_CreateTexture(this->main, format, access, w, h); }
                    SDL_Texture* create_texture_from_surface(SDL_Surface* surface) { return SDL_CreateTextureFromSurface(this->main, surface); }

                    void destroy_renderer() { SDL_DestroyRenderer(this->main); }

                    int get_render_draw_blend_mode(SDL_BlendMode* blend_mode) { return SDL_GetRenderDrawBlendMode(this->main, blend_mode); }
                    int get_render_draw_color(std::uint8_t* r, std::uint8_t* g, std::uint8_t* b,
                                              std::uint8_t* a) { return SDL_GetRenderDrawColor(this->main, r, g, b, a); }
                    int get_renderer_info(SDL_RendererInfo* info) { return SDL_GetRendererInfo(this->main, info); }
                    int get_renderer_output_size(int* w, int* h) { return SDL_GetRendererOutputSize(this->main, w, h); }

                    SDL_Texture* get_render_target() { return SDL_GetRenderTarget(this->main); }

                    int render_clear() { return SDL_RenderClear(this->main); }
                    int render_copy(SDL_Texture* texture, const sdl4::video::rect::rect src,
                                    const sdl4::video::rect::rect dst) { return SDL_RenderCopy(this->main, texture, src.main, dst.main); }
                    int render_draw_line(int x1, int y1, int x2, int y2) { return SDL_RenderDrawLine(this->main, x1, y1, x2, y2); }
                    int render_draw_point(int x1, int y1) { return SDL_RenderDrawPoint(this->main, x1, y1); }
                    int render_draw_rect(const sdl4::video::rect::rect rc) { return SDL_RenderDrawRect(this->main, rc.main); }
                    int render_fill_rect(const sdl4::video::rect::rect rc) { return SDL_RenderFillRect(this->main, rc.main); }

                    void render_get_clip_rect(sdl4::video::rect::rect rc) { SDL_RenderGetClipRect(this->main, rc.main); }

                    bool render_get_integer_scale() { return ((SDL_RenderGetIntegerScale(this->main) == SDL_bool::SDL_TRUE) ? true : false); }

                    void render_get_logical_scale(int* w, int* h) { SDL_RenderGetLogicalSize(this->main, w, h); }
                    void render_get_scale(float* x, float* y) { SDL_RenderGetScale(this->main, x, y); }
                    void render_get_viewport(sdl4::video::rect::rect rc) { SDL_RenderGetViewport(this->main, rc.main); }

                    bool render_is_clip_enable() { return ((SDL_RenderIsClipEnabled(this->main) == SDL_bool::SDL_TRUE) ? true : false); }

                    void render_present() { SDL_RenderPresent(this->main); }

                    template<typename Pixel>
                    int render_read_pixels(const sdl4::video::rect::rect rc, std::uint32_t format, Pixel pixels, int pitch) {
                        return SDL_RenderReadPixels(this->main, rc.main, format, pixels, pitch);
                    }
                    int render_set_clip_rect(const sdl4::video::rect::rect rc) { return SDL_RenderSetClipRect(this->main, rc.main); }
                    int render_set_integer_scale(bool enable) { return SDL_RenderSetIntegerScale(this->main, (enable) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE); }
                    int render_set_logical_scale(int w, int h) { return SDL_RenderSetLogicalSize(this->main, w, h); }
                    int render_set_scale(float x, float y) { return SDL_RenderSetScale(this->main, x, y); }
                    int render_set_viewport(const sdl4::video::rect::rect rc) { return SDL_RenderSetViewport(this->main, rc.main); }

                    bool render_target_supported() { return ((SDL_RenderTargetSupported(this->main) == SDL_bool::SDL_TRUE) ? true : false); }

                    int set_render_draw_blend_mode(SDL_BlendMode blend_mode) { return SDL_SetRenderDrawBlendMode(this->main, blend_mode); }
                    int set_render_draw_color(std::uint8_t r, std::uint8_t g, std::uint8_t b,
                                              std::uint8_t a) { return SDL_SetRenderDrawColor(this->main, r, g, b, a); }
                    int set_render_target(SDL_Texture* texture) { return SDL_SetRenderTarget(this->main, texture); }
                };

                SDL_BlendMode compose_custom_blend_mode(SDL_BlendFactor src_cf, SDL_BlendFactor dst_cf,
                                                        SDL_BlendOperation color_operation,
                                                        SDL_BlendFactor src_af, SDL_BlendFactor dst_af,
                                                        SDL_BlendOperation alpha_operation) {
                    return SDL_ComposeCustomBlendMode(src_cf, dst_cf, color_operation, src_af, dst_af, alpha_operation);
                }

                void destroy_texture(SDL_Texture* texture) { SDL_DestroyTexture(texture); }

                int get_num_render_drivers() { return SDL_GetNumRenderDrivers(); }
                int get_render_driver_info(int index, SDL_RendererInfo* info) { return SDL_GetRenderDriverInfo(index, info); }
                int get_texture_alpha_mod(SDL_Texture* texture, std::uint8_t* alpha) { return SDL_GetTextureAlphaMod(texture, alpha); }
                int get_texture_blend_mode(SDL_Texture* texture, SDL_BlendMode* blend_mode) { return SDL_GetTextureBlendMode(texture, blend_mode); }
                int get_texture_color_mod(SDL_Texture* texture, std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) { return SDL_GetTextureColorMod(texture, r, g, b); }
                int query_texture(SDL_Texture* texture, std::uint32_t* format, int* access, int* w, int* h) { return SDL_QueryTexture(texture, format, access, w, h); }
                int set_texture_alpha_mod(SDL_Texture* texture, std::uint8_t alpha) { return SDL_SetTextureAlphaMod(texture, alpha); }
                int set_texture_blend_mode(SDL_Texture* texture,
                                           SDL_BlendMode blend_mode) { return SDL_SetTextureBlendMode(texture, blend_mode); }
                int set_texture_color_mod(SDL_Texture* texture,
                                          std::uint8_t r, std::uint8_t g, std::uint8_t b) { return SDL_SetTextureColorMod(texture, r, g, b); }

                void unlock_texture(SDL_Texture* texture) { SDL_UnlockTexture(texture); }

                template<typename Pixel>
                int update_texture(SDL_Texture* texture, const sdl4::video::rect::rect rc, const Pixel pixels, int pitch) {
                    return SDL_UpdateTexture(texture, rc.main, pixels, pitch);
                }
                int update_yuv_texture(SDL_Texture* texture, const sdl4::video::rect::rect rc,
                                       const std::uint8_t* y_plane, int y_pitch,
                                       const std::uint8_t* u_plane, int u_pitch,
                                       const std::uint8_t* v_plane, int v_pitch) {
                    return SDL_UpdateYUVTexture(texture, rc.main,
                                                y_plane, y_pitch,
                                                u_plane, u_pitch,
                                                v_plane, v_pitch);
                }
            }

            class window {
            public:
                SDL_Window* main;
            public:
                window() = default; ~window() { this->destroy(); };

                void create_window(const std::string title,
                            int x, int y, int w, int h,
                            std::uint32_t flags) {
                    this->main = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
                }

                int create_window_and_renderer(int w, int h,
                                               std::uint32_t window_flags, sdl4::video::window::renderer::renderer rnd) {
                    return SDL_CreateWindowAndRenderer(w, h, window_flags, &this->main, &rnd.main);
                }

                template<typename Data>
                void create_from(const Data data) {
                    this->main = SDL_CreateWindowFrom(data);
                }

                void destroy() {
                    SDL_DestroyWindow(this->main);
                }

                window get_grabbed_window() {
                    auto val = SDL_GetGrabbedWindow();
                    return sdl4::video::window::window { .main = val };
                }

                int get_window_borders_size(int* top, int* left, int* bottom, int* right) {
                    return SDL_GetWindowBordersSize(this->main, top, left, bottom, right);
                }

                float get_window_brightness() {
                    return SDL_GetWindowBrightness(this->main);
                }

                template<typename Data>
                Data get_window_data(const std::string name) {
                    return SDL_GetWindowData(this->main, name.c_str());
                }

                int get_dp_index() {
                    return SDL_GetWindowDisplayIndex(this->main);
                }

                template<typename DriverType>
                int get_window_dm(sdl4::video::display::mode<DriverType> __mode) {
                    return SDL_GetWindowDisplayMode(this->main,
                                                    sdl4::video::display::mode<DriverType>::to(__mode));
                }

                std::uint32_t get_window_flags() {
                    return SDL_GetWindowFlags(this->main);
                }

                int get_window_gamma_ramp(std::uint16_t* red, std::uint16_t* green, std::uint16_t* blue) {
                    return SDL_GetWindowGammaRamp(this->main, red, green, blue);
                }

                bool get_window_grab() {
                    return ((SDL_GetWindowGrab(this->main) == SDL_bool::SDL_TRUE) ? true : false);
                }

                std::uint32_t get_window_id() {
                    return SDL_GetWindowID(this->main);
                }

                void get_window_maximum_size(int* w, int* h) {
                    SDL_GetWindowMaximumSize(this->main, w, h);
                }

                void get_window_minimum(int* w, int* h) {
                    SDL_GetWindowMinimumSize(this->main, w, h);
                }

                int get_window_opacity(float* out_opacity) {
                    return SDL_GetWindowOpacity(this->main, out_opacity);
                }

                std::uint32_t get_window_pixel_format() {
                    return SDL_GetWindowPixelFormat(this->main);
                }

                void get_window_position(int* x, int* y) {
                    return SDL_GetWindowPosition(this->main, x, y);
                }

                void get_window_size(int* w, int* h) {
                    return SDL_GetWindowSize(this->main, w, h);
                }

                SDL_Surface* get_window_surface() {
                    return SDL_GetWindowSurface(this->main);
                }

                const std::string get_window_title() {
                    return sdl4::convert(SDL_GetWindowTitle(this->main));
                }

                bool get_window_wm_info(SDL_SysWMinfo* info) {
                    return ((SDL_GetWindowWMInfo(this->main, info) == SDL_bool::SDL_TRUE) ? true : false);
                }

                void get_drawable_size(int* w, int* h) { SDL_GL_GetDrawableSize(this->main, w, h); }
                void gl_swap_window() { SDL_GL_SwapWindow(this->main); }
                void hide_window() { SDL_HideWindow(this->main); }
                void maximize_window() { SDL_MaximizeWindow(this->main); }
                void minimize_window() { SDL_MinimizeWindow(this->main); }
                void raise_window() { SDL_RaiseWindow(this->main); }
                void restore_window() { SDL_RestoreWindow(this->main); }

                void set_window_bordered(bool bordered) {
                    ((SDL_SetWindowBordered(this->main, ((bordered) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE))));
                }

                int set_window_brightness(float brightness) { return SDL_SetWindowBrightness(this->main, brightness); }

                template<typename Data, typename AnotherData>
                AnotherData set_window_data(const std::string name, Data user_data) {
                    return SDL_SetWindowData(this->main, name.c_str(), user_data);
                }

                template<typename DriverType>
                int set_window_display_mode(const sdl4::video::display::mode<DriverType> __mode) {
                    return SDL_SetWindowDisplayMode(this->main, sdl4::video::display::mode<DriverType>::to(__mode));
                }

                int set_window_fullscreen(std::uint32_t flags) { return SDL_SetWindowFullscreen(this->main, flags); }

                int set_window_gamma_ramp(const std::uint16_t* red,
                                          const std::uint16_t* green,
                                          const std::uint16_t* blue) {
                    return SDL_SetWindowGammaRamp(this->main, red, green, blue);
                }

                void set_window_grab(bool grabbed) {
                    SDL_SetWindowGrab(this->main, (grabbed) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE);
                }

                template<typename CallbackData>
                int set_window_hit_test(SDL_HitTest cb, CallbackData cb_data) {
                    return SDL_SetWindowHitTest(this->main, cb, cb_data);
                }

                void set_window_icon(SDL_Surface* icon) { SDL_SetWindowIcon(this->main, icon); }

                int set_window_input_focus() { return SDL_SetWindowInputFocus(this->main); }

                void set_window_maximum_size(int max_w, int max_h) { SDL_SetWindowMaximumSize(this->main, max_w, max_h); }
                void set_window_minimum_size(int min_w, int min_h) { SDL_SetWindowMinimumSize(this->main, min_w, min_h); }

                int set_window_opacity(float opacity) { return SDL_SetWindowOpacity(this->main, opacity); }

                void set_window_position(int x, int y) { SDL_SetWindowPosition(this->main, x, y); }
                void set_window_resizable(bool resizable) { SDL_SetWindowResizable(this->main,
                                                                                   (resizable) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE); }
                void set_window_size(int w, int h) { SDL_SetWindowSize(this->main, w, h); }
                void set_window_title(const std::string title) { SDL_SetWindowTitle(this->main, title.c_str()); }

                int show_simple_message_box(std::uint32_t flags, const std::string title, const std::string message) {
                    return SDL_ShowSimpleMessageBox(flags, title.c_str(), message.c_str(), this->main);
                }

                void show_window() { SDL_ShowWindow(this->main); }

                int update_window_surface() { return SDL_UpdateWindowSurface(this->main); }
                int update_window_surface_rects(const rect::rect rects, int num_rects) { return SDL_UpdateWindowSurfaceRects(this->main, rects.main, num_rects); }

                sdl4::video::window::renderer::renderer create_renderer(int index, std::uint32_t flags) {
                    return sdl4::video::window::renderer::renderer { .main = SDL_CreateRenderer(this->main, index, flags) };
                }

                int create_window_and_renderer(int w, int h, std::uint32_t window_flags, sdl4::video::window::renderer::renderer* rnd) {
                    return SDL_CreateWindowAndRenderer(w, h, window_flags, &this->main, &rnd->main);
                }

                sdl4::video::window::renderer::renderer get_renderer() {
                    return sdl4::video::window::renderer::renderer { .main = SDL_GetRenderer(this->main) };
                }
            };

            window get_window_from_id(std::uint32_t id) {
                auto val = SDL_GetWindowFromID(id);
                return sdl4::video::window::window { .main = val };
            }

            int set_window_modal_for(window modal_window, window parent_window) { return SDL_SetWindowModalFor(modal_window.main, parent_window.main); }
            int show_message_box(const SDL_MessageBoxData* message_box_data, int* button_id) { return SDL_ShowMessageBox(message_box_data, button_id); }
        }


        namespace context {
            namespace gl {
                class context {
                public:
                    SDL_GLContext* main;
                public:
                    context() = default; ~context() { this->delete_context(); };

                    context create_context(sdl4::video::window::window data) {
                        auto val = SDL_GL_CreateContext(data.main);
                        return context { .main = &val };
                    }

                    void delete_context() {
                        SDL_GL_DeleteContext(this->main);
                    }

                    context get_current_context() {
                        auto val = SDL_GL_GetCurrentContext();
                        return sdl4::video::context::gl::context { .main = &val };
                    }

                    int make_current(sdl4::video::window::window wnd) {
                        return SDL_GL_MakeCurrent(wnd.main, this->main);
                    }
                };

                bool extension_supported(const std::string extension) { return ((SDL_GL_ExtensionSupported(extension.c_str()) == SDL_bool::SDL_TRUE) ? true : false); }
                int get_attribute(SDL_GLattr attr, int* value) { return SDL_GL_GetAttribute(attr, value); }
                int set_attribute(SDL_GLattr attr, int value) { return SDL_GL_SetAttribute(attr, value); }
                int get_swap_interval() { return SDL_GL_GetSwapInterval(); }
                int set_swap_interval(int interval) { return SDL_GL_SetSwapInterval(interval); }
                int load_library(const std::string path) { return SDL_GL_LoadLibrary(path.c_str()); }


                sdl4::video::window::window get_current_window() {
                    auto val = SDL_GL_GetCurrentWindow();
                    return sdl4::video::window::window { .main = val };
                }

                template<typename Address> Address get_proc_address(const std::string proc) { return SDL_GL_GetProcAddress(proc.c_str()); }

                void reset_attributes() { SDL_GL_ResetAttributes(); }
                void unload_library() { SDL_GL_UnloadLibrary(); }

                int bind_texture(SDL_Texture* texture, float* tex_w, float* tex_h) { return SDL_GL_BindTexture(texture, tex_w, tex_h); }
                int unbind_texture(SDL_Texture* texture) { return SDL_GL_UnbindTexture(texture); }
            }
        }

        void enable_screen_saver() { SDL_EnableScreenSaver(); }
        void disable_screen_saver() { SDL_DisableScreenSaver(); }

        bool is_screen_saver_enabled() { return ((SDL_IsScreenSaverEnabled() == SDL_bool::SDL_TRUE) ? true : false); }

        int init(const std::string driver_name) { return SDL_VideoInit(driver_name.c_str()); }

        void quit() { SDL_VideoQuit(); }
    }
}

#endif // SDL4CPP_VIDEO_HPP
