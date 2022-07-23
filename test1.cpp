#include <popt.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // These values will be auto filled.
    char *type = NULL;
    char *file = NULL;
    int count = 0;
    int help = 0;
    int version = 0;

    //
    // 1, prepare options.
    //
    // if (poptOption.val > 0) then this val is equivalent to option-id,
    // and poptGetNextOpt(ctx) will suspend from parsing at this option.
    //
    struct poptOption options[] = {
        {"type", 't', POPT_ARG_STRING, &type, 1, "specify file type", "type"},
        {"file", 'n', POPT_ARG_STRING, &file, 2, "specify file name", "file"},
        {"count", 'c', POPT_ARG_INT, &count, 3, "specify file count", "count"},
        {"help", 'h', POPT_ARG_NONE, &help, 4, "show help", "debug"},
        {"version", 'v', POPT_ARG_NONE, &version, 5, "show version", "version"},
        {NULL, 0, 0, NULL, 0, NULL, NULL}};

    // 2, get option context.
    poptContext ctx =
        poptGetContext("MyApp", argc, (const char **)argv, options, 0);

    //
    // 3, parse args and check result.
    //
    // Because poptGetNextOpt(ctx) will suspend from parsing at every option,
    // A while loop should be used.
    //
    int rc;
    while ((rc = poptGetNextOpt(ctx)) > 0) {
        printf("option-id = %d, option-arg = %s\n", rc, poptGetOptArg(ctx));
    }

    if (rc != -1) {
        printf("error: %s", poptStrerror(rc));
        if (poptBadOption(ctx, 0)) {
            printf(", bad option or argument: %s", poptBadOption(ctx, 0));
        }
        printf("\n");
    }

    const char *remanent;
    while ((remanent = poptGetArg(ctx)) != nullptr) {
        printf("remanent-arg = %s\n", remanent);
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