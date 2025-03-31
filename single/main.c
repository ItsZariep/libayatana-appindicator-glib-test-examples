#include <ayatana-appindicator.h>
#include <glib.h>

static void on_option1_activate(GSimpleAction *action, GVariant *param, gpointer user_data) {
	g_print("Option 1 selected\n");
}

static void on_quit_activate(GSimpleAction *action, GVariant *param, gpointer user_data) {
	GMainLoop *loop = (GMainLoop *)user_data;
	g_main_loop_quit(loop);
}

int main(int argc, char **argv) {
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);
	
	// Create the indicator
	AppIndicator *indicator = app_indicator_new("start-here", "indicator-messages", APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
	app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);

	// Create menu
	GMenu *menu = g_menu_new();
	GSimpleActionGroup *actions = g_simple_action_group_new();

	// "Option 1" menu item
	GSimpleAction *option1_action = g_simple_action_new("option1", NULL);
	g_signal_connect(option1_action, "activate", G_CALLBACK(on_option1_activate), NULL);
	g_action_map_add_action(G_ACTION_MAP(actions), G_ACTION(option1_action));
	g_object_unref(option1_action);

	GMenuItem *option1_item = g_menu_item_new("Option 1", "indicator.option1");
	g_menu_append_item(menu, option1_item);
	g_object_unref(option1_item);

	// "Quit" menu item
	GSimpleAction *quit_action = g_simple_action_new("quit", NULL);
	g_signal_connect(quit_action, "activate", G_CALLBACK(on_quit_activate), loop);
	g_action_map_add_action(G_ACTION_MAP(actions), G_ACTION(quit_action));
	g_object_unref(quit_action);

	GMenuItem *quit_item = g_menu_item_new("Quit", "indicator.quit");
	g_menu_append_item(menu, quit_item);
	g_object_unref(quit_item);

	// Attach menu and actions to indicator
	app_indicator_set_menu(indicator, menu);
	app_indicator_set_actions(indicator, actions);

	g_object_unref(menu);
	g_object_unref(actions);

	// Run the main loop
	g_main_loop_run(loop);

	// Cleanup
	g_main_loop_unref(loop);
	return 0;
}
