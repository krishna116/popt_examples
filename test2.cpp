#include <popt.h>
#include <stdio.h>

//
// The callback could be used as a global filter
// or validator for any option and option-argument.
//
void callback(poptContext con, enum poptCallbackReason reason,
              const struct poptOption *opt, const char *arg, const void *data) {
    printf("[callback] ");
    if (opt->longName) {
        printf("option = %s", opt->longName);
    } else {
        printf("option = %c", opt->shortName);
    }
    printf(", arg = %s", arg);
    printf(", data = %s\n", (const char *)data);
}

int main(int argc, char *argv[]) {
    char *type = NULL;
    char *file = NULL;
    int count = 0;
    int help = 0;
    int version = 0;

    //
    // 1, prepare options.
    //
    // if(poptOption.val == 0), when execute poptGetNextOpt(ctx),
    // it won't suspend from parsing at this option and just continue to process
    // next item.
    //
    struct poptOption options[] = {
        {NULL, NULL, POPT_ARG_CALLBACK, (void *)callback, 0, NULL, NULL},
        {"type", 't', POPT_ARG_STRING, &type, 0, "specify file type", "type"},
        {"file", 'n', POPT_ARG_STRING, &file, 0, "specify file name", "file"},
        {"count", 'c', POPT_ARG_INT, &count, 0, "specify count", "count"},
        {"help", 'h', POPT_ARG_NONE, &help, 0, "show help", "debug"},
        {"version", 'v', POPT_ARG_NONE, &version, 0, "show version", "version"},
        {NULL, 0, 0, NULL, 0, NULL, NULL}};

    // 2, get option context.
    poptContext ctx =
        poptGetContext("MyApp", argc, (const char **)argv, options, 0);

    // 3, parse args and check result, a while loop do not needed.
    int rc = poptGetNextOpt(ctx);
    if (rc != -1) {
        printf("error: %s", poptStrerror(rc));
        if (poptBadOption(ctx, 0)) {
            printf(", bad option or argument: %s", poptBadOption(ctx, 0));
        }
        printf("\n");
    }

    // 4, free option context.
    ctx = poptFreeContext(ctx);

    //
    // 5, prosess result.
    //
    printf("help = %d\n", help);
    printf("version = %d\n", version);
    printf("type  = %s\n", type);
    printf("file  = %s\n", file);
    printf("count = %d\n", count);

    return 0;
}