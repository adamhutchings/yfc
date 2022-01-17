#include "compiler-backend.h"

#include <string.h>

#include <util/allocator.h>
#include <util/yfc-out.h>

int create_output_file_name(
    struct yf_file_compilation_data * data, struct yf_args * args
) {

    const char * namebuf_copyloc;

    data->output_file = yf_malloc(sizeof (char) * 256);
    if (!data->output_file)
        return 1;

    /* Normal: foo/bar/baz.yf -> foo/bar/baz.c */
    /* with --project: src/foo/bar/baz.yf -> bin/c/foo/bar/baz.c */
    if (args->project) {
        strcpy(data->output_file, "bin/c/");
        namebuf_copyloc = data->file_name + strlen("src/");
        strcat(data->output_file, namebuf_copyloc);
        /* Change .yf to .c */
        /* FIRST, check for .yf ending */
        if (strlen(data->output_file) > 3 &&
            strcmp(data->output_file + strlen(data->output_file) - 3, ".yf") == 0) {
            /* Simply tack on .c */
            /* But no .yf is bad */
            strcat(data->output_file, ".c");
            YF_PRINT_WARNING(
                "file %s does not end with .yf", data->output_file
            );
        } else {
            strcpy(data->output_file + strlen(namebuf_copyloc) - 2, "c");
        }
    } else {
        /* Replace .yf with .c */
        /* TODO - reduce code copying from above */
        namebuf_copyloc = data->file_name;
        strcat(data->output_file, namebuf_copyloc);
        if (strlen(data->output_file) > 3 &&
            strcmp(data->output_file + strlen(data->output_file) - 3, ".yf")) {
            /* Simply tack on .c */
            /* But no .yf is bad */
            YF_PRINT_WARNING(
                "file %s does not end with .yf", data->output_file
            );
            strcat(data->output_file, ".c");
        } else {
            strcpy(data->output_file + strlen(namebuf_copyloc) - 2, "c");
        }
    }

    return 0;

}

/**
 * Generate C code, run the C compiler, and link the resulting binary.
 */
int yf_run_backend(
    struct yf_project_compilation_data * data, struct yf_args * args
) {
    
    int i;
    struct yf_file_compilation_data * file;

    for (i = 0; i < data->num_files; ++i) {
        file = data->files[i];
        if (file->error)
            continue;
        create_output_file_name(file, args);
    }

    return 0;

}
