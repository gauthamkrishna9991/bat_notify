#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <libnotify/notify.h>

// Path to battery info
static const char *BATTERY_ROOT_PATH = "/sys/class/power_supply/BAT0/";
// to find charge level
static const char *CHARGE_NOW = "charge_now";
// to find battery capacity
static const char *CHARGE_FULL = "charge_full";
// adapter status
static const char *ADAPTER_ONLINE_PATH = "/sys/class/power_supply/ADP1/online";

// Battery Threshold Lmimits
static const float LOWER_THRESHOLD = 0.60;
static const float HIGHER_THRESHOLD = 0.80;

// Sleep time in seconds
const int SLEEP_TIME = 5;

volatile sig_atomic_t keepAlive = true;

long int read_battery_level(const char* battery_file_path) {
	FILE *fp = fopen(battery_file_path, "r");
	long int x = 0;
	fscanf(fp, "%ld", &x);
	fclose(fp);
	return x;
}

static void exit_handler(int _) {
	(void)_;
	keepAlive = false;
}

void print_startup() {
	// Doesn't look good here, but when you execute it, it would look good.
	char* BAT_NOTIFY_HEADER = "\n"
		"########     ###    ########         ##    ##  #######  ######## #### ######## ##    ## \n"
		"##     ##   ## ##      ##            ###   ## ##     ##    ##     ##  ##        ##  ##  \n"
		"##     ##  ##   ##     ##            ####  ## ##     ##    ##     ##  ##         ####   \n"
		"########  ##     ##    ##            ## ## ## ##     ##    ##     ##  ######      ##    \n"
		"##     ## #########    ##            ##  #### ##     ##    ##     ##  ##          ##    \n"
		"##     ## ##     ##    ##            ##   ### ##     ##    ##     ##  ##          ##    \n"
		"########  ##     ##    ##    ####### ##    ##  #######     ##    #### ##          ##    \n";
	printf("%s\n",BAT_NOTIFY_HEADER);
	printf("The battery reporting superhero.\n");
}

int main() {
	// BEFORE START: Set up all paths for us.
	char capacity_path[strlen(BATTERY_ROOT_PATH) + strlen(CHARGE_FULL) + 1];
	char level_path[strlen(BATTERY_ROOT_PATH) + strlen(CHARGE_NOW) + 1];
	strcpy(capacity_path, BATTERY_ROOT_PATH);
	strcat(capacity_path, CHARGE_FULL);
	strcpy(level_path, BATTERY_ROOT_PATH);
	strcat(level_path, CHARGE_NOW);
	// PROGRAM STARTS HERE
	// Signal Handling for Interrupt Signal
	signal(SIGINT, exit_handler);

	print_startup();
	// Get Battery Capacity
	const long battery_capacity = read_battery_level(capacity_path);
	printf("Total Battery Capacity: %ld\n", battery_capacity);

	// Initialize Notification Library
	notify_init ("com.github.gauthamkrishna9991.bat_notify");
	// Set up Notification Object
	while (keepAlive) {
		// Calculate the battery level
		float battery_level = (float)read_battery_level(level_path)/(float)battery_capacity;
		// IF battery level is higher than threshold AND is charging
		if (battery_level > HIGHER_THRESHOLD && read_battery_level(ADAPTER_ONLINE_PATH) == 1) {
			char connect_charger_message[200];
			sprintf(connect_charger_message, "%f%% REMAINING (>%d%%).", battery_level * 100, (int)(HIGHER_THRESHOLD * 100));
			NotifyNotification * battery_over_threshold_notify = notify_notification_new ("Disconnect Charger", connect_charger_message, "battery-caution-symbolic");
			notify_notification_show (battery_over_threshold_notify, NULL);
			g_object_unref(G_OBJECT(battery_over_threshold_notify));
		} else if (battery_level < LOWER_THRESHOLD && read_battery_level(ADAPTER_ONLINE_PATH) == 0) {
			char disconnect_charger_message[200];
			sprintf(disconnect_charger_message, "%f%% REMAINING (<%d%%).", battery_level * 100, (int)(LOWER_THRESHOLD * 100));
			NotifyNotification *battery_under_threshold_notify = notify_notification_new ("Connect Charger", disconnect_charger_message, "battery-low-charging-symbolic");
			notify_notification_show (battery_under_threshold_notify, NULL);
			g_object_unref(G_OBJECT(battery_under_threshold_notify));
		}
		sleep(SLEEP_TIME);
	}
	return 0;
	notify_uninit();
}
