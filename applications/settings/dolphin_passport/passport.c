#include "assets_icons.h"
#include "dolphin/helpers/dolphin_state.h"
#include <core/check.h>
#include <core/record.h>
#include <furi.h>
#include <gui/gui.h>
#include <furi_hal_version.h>
#include "dolphin/dolphin.h"
#include "../desktop_settings/desktop_settings_app.h"
#include "math.h"

#define MOODS_TOTAL 3
#define BUTTHURT_MAX 3

// LIST OF PROFILE PICTS -> CALLED BY BUTTHURT THEN BY LEVEL 
static const Icon* const portrait_happy[BUTTHURT_MAX] = {
    &I_passport_happy1_46x49,
    &I_passport_happy2_46x49,
    &I_passport_happy3_46x49};
static const Icon* const portrait_ok[BUTTHURT_MAX] = {
    &I_passport_okay1_46x49,
    &I_passport_okay2_46x49,
    &I_passport_okay3_46x49};
static const Icon* const portrait_bad[BUTTHURT_MAX] = {
    &I_passport_bad1_46x49,
    &I_passport_bad2_46x49,
    &I_passport_bad3_46x49};

// Getting rid of portrait_ok and portrait_bad would result in non changing pict whatever the mood) 
static const Icon* const* portraits[MOODS_TOTAL] = {portrait_happy, portrait_ok, portrait_bad};

static void input_callback(InputEvent* input, void* ctx) {
    FuriSemaphore* semaphore = ctx;

    if((input->type == InputTypeShort) && (input->key == InputKeyBack)) {
        furi_semaphore_release(semaphore);
    }
}

static void render_callback(Canvas* canvas, void* ctx) {
    DolphinStats* stats = ctx;

    DesktopSettings* settings = malloc(sizeof(DesktopSettings));
    DESKTOP_SETTINGS_LOAD(settings);

    // STRENGHT VALUES OF LVL / XP / MOOD
    char level_str[20];
    char xp_str[12];
    char mood_str[32];
    uint8_t mood = 0;
    
    // BUTTHURT VALUES FOR MOOD CHANGING + MOOD NAMING
    if(stats->butthurt <= 4) {
        mood = 0;
        snprintf(mood_str, 20, "Mood: Squachy !");
    } else if(stats->butthurt <= 9) {
        mood = 1;
        snprintf(mood_str, 20, "Mood: Meh");
    } else {
        mood = 2;
        snprintf(mood_str, 20, "Mood: Heated");
    }

    // LVL UP VIA XP
    uint32_t xp_progress = 0;
    uint32_t xp_to_levelup = dolphin_state_xp_to_levelup(stats->icounter);
    uint32_t xp_above_last_levelup = dolphin_state_xp_above_last_levelup(stats->icounter);
    uint32_t xp_for_current_level = xp_to_levelup + xp_above_last_levelup;
    
    // MAX LVL
    if(stats->level == 30) {
        xp_progress = 0;
    } else {
        xp_progress = xp_to_levelup * 64 / xp_for_current_level;
    }

    // multipass
    // HERE POSITION AND NAME OF PASSPORT BACKGROUND PICT
    canvas_draw_icon(canvas, 0, 0, &I_passport_mountains);
    // OFW Passport : LEFT + BOTTOM BORDERS + UPPER & RIGHT LINES + DOT
       //canvas_draw_icon(canvas, 0, 0, &I_passport_left_6x46);
       //canvas_draw_icon(canvas, 0, 46, &I_passport_bottom_128x18);
       //canvas_draw_line(canvas, 6, 0, 125, 0);
       //canvas_draw_line(canvas, 127, 2, 127, 47);
       //canvas_draw_dot(canvas, 126, 1);

    // portrait
    // PROFILE PICT CHANGE ACCORDING TO LEVEL
    furi_assert((stats->level > 0) && (stats->level <= 30));
    uint16_t tmpLv1 = 0;
    // POSITION OF PROFILE PICT (ofw : 9,5) + Value for LVL changing pict
    canvas_draw_icon(canvas, 11, 2, portraits[mood][tmpLv1]);
    
    // CODED LINES (Useless with full screen background pict) :
       // canvas_draw_line(canvas, 58, 16, 123, 16);
       // canvas_draw_line(canvas, 58, 30, 123, 30);
       // canvas_draw_line(canvas, 58, 44, 123, 44);
    
    // CALL FLIPPER NAME
    const char* my_name = furi_hal_version_get_name_ptr();
    // LEVEL DISPLAY
    snprintf(level_str, 12, "Level: %hu", stats->level);
    // XP / XP DISPLAY
    snprintf(xp_str, 12, "%lu/%lu", xp_above_last_levelup, xp_for_current_level);
    canvas_set_font(canvas, FontSecondary);
    // POSITION OF NAME (58,12 ofw) -> TO CUSTOM NAME : change [my_name ? my_name] to [my_name ? "WHATYOUWANT"]
    canvas_draw_str(canvas, 58, 10, my_name ? my_name : "Unknown");
    // POSITION OF MOOD (58,26 ofw): 
    canvas_draw_str(canvas, 58, 22, mood_str);
    canvas_set_color(canvas, ColorBlack);
    // POSITION OF LEVEL (58,40 ofw):
    canvas_draw_str(canvas, 58, 34, level_str);
    // POSITION OF XP / XP
    canvas_draw_str(canvas, 58, 42, xp_str);
    // POSITION AND SIZE OF XP BAR (123... 47... +1, 6 [bar thickness] ofw)
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_box(canvas, 123 - xp_progress, 45, xp_progress + 1, 5);
    canvas_set_color(canvas, ColorBlack);
    //Useless with full screen background pict with drawn XP bar :
    //canvas_draw_line(canvas, 123, 47, 123, 52);
    free(settings);
}

int32_t passport_app(void* p) {
    UNUSED(p);
    FuriSemaphore* semaphore = furi_semaphore_alloc(1, 0);
    furi_assert(semaphore);

    ViewPort* view_port = view_port_alloc();

    Dolphin* dolphin = furi_record_open(RECORD_DOLPHIN);
    DolphinStats stats = dolphin_stats(dolphin);
    furi_record_close(RECORD_DOLPHIN);
    view_port_draw_callback_set(view_port, render_callback, &stats);
    view_port_input_callback_set(view_port, input_callback, semaphore);
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);
    view_port_update(view_port);

    furi_check(furi_semaphore_acquire(semaphore, FuriWaitForever) == FuriStatusOk);

    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    furi_semaphore_free(semaphore);

    return 0;
}
