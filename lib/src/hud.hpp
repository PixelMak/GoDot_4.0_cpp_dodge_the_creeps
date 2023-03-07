#ifndef GDEXTENSION_HUD_H
#define GDEXTENSION_HUD_H

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/variant/string.hpp>

namespace game_lib
{
  using namespace godot;

  class HUD : public CanvasLayer
  {
    GDCLASS(HUD, CanvasLayer)

    Label* _score_label;
    Label* _message_label;
    Timer* _start_message_timer;
    Timer* _get_ready_message_timer;
    Button* _start_button;
    Timer* _start_button_timer;

  protected:
    static void _bind_methods();

  public:
    void _ready();
    void show_get_ready();
    void show_game_over();
    void update_score(const int p_score);
    void _on_StartButton_pressed();
    void _on_StartMessageTimer_timeout();
    void _on_GetReadyMessageTimer_timeout();
  };
}

#endif // GDEXTENSION_HUD_H