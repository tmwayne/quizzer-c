/* argparse.h */

#include <argp.h>

const char* argp_program_version = "C Cookie-Cutter 0.0\n"
  "Copyright © 2020 Tyler Wayne";

const char* argp_program_bug_address = "<tylerwayne3@gmail.com>";

// This structure is used by main to communicate with parse_opt.
struct arguments {
  char *args[1];      // Positional argument
  char *with;         // Optional argument with value
  int  without;       // Optional argument without value
};

/*
 * OPTIONS : Field 1 in Argp
 * Order of fields: { name, key, arg, flags, doc }
 */
static struct argp_option options[] = {
  {"with-value", 'a', "file", 0, "Optional argument with value"},
  {"without-value", 'b', 0, 0, "Optional argument without value"},
  {0}
};

/*
 * PARSER : Field 2 in Argp
 * Order of parameters: key, arg, state
 */
static error_t parse_opt(int key, char* arg, struct argp_state* state) {
  struct arguments* arguments = state->input;

  switch (key) {
    case 'a':
      arguments->with = arg;
      break;
    case 'b':
      arguments->without = 1;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        argp_usage(state);
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
        argp_usage(state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

/*
 * ARGS_DOC : Field 3 in Argp
 * A description of the non-option command-line arguments that we accepted
 */
static char args_doc[] = "positional-arg";

/*
 * DOC : Field 4 in Argp
 * Program documentation
 */
static char doc[] = "someprog -- template program for cookie-cutter";

/*
 * Argp structure
 */
static struct argp argp = { options, parse_opt, args_doc, doc };

