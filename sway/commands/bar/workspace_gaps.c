#include <stdlib.h>
#include <strings.h>
#include "config.h"
#include "sway/commands.h"
#include "sway/config.h"
#include "log.h"

struct cmd_results *bar_cmd_workspace_gaps(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "workspace_gaps", EXPECTED_AT_LEAST, 0))) {
		return error;
	}

	struct bar_config *bar = config->current_bar;

	char *end;
	int gaps = strtol(argv[0], &end, 10);
	if (gaps < 0 || (*end != '\0' && strcasecmp(end, "px") != 0)) {
		return cmd_results_new(CMD_INVALID,
				"[Bar %s] Invalid workspace button gap width value: %s",
				bar->id, argv[0]);
	}

	if (argc == 2 && strcasecmp(argv[1], "px") != 0) {
		return cmd_results_new(CMD_INVALID,
				"Expected 'workspace_gaps <px> [px]'");
	}

	sway_log(SWAY_DEBUG, "[Bar %s] Setting workspace button gap width to %d",
			bar->id, gaps);
	config->current_bar->workspace_gaps = gaps;
	return cmd_results_new(CMD_SUCCESS, NULL);
}
