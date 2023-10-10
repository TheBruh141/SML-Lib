//
// Created by bruh on 10/7/23.
//

#include <stdio.h>
#include "modules/errors_and_logging.h"
#include "modules/common_bindings.h"
#include "modules/math.h"

int main(void) {
    printf("hello you!\n");
    printf("this is a file where you can try sml_lib without copying it :D\n");

    sml_error_config err_conf = init_sml_error(
            "SML_SANDBOX",
            false,
            NULL
    );

    // math.h does not rely on any preexisting math library. Let's check accuracy!
    printf("%f", LOGARITHM_ACC);

    // since we know that sin^2 + cos^2 = 1
    for (sml_size_t degree = 0; degree < 90; degree++) {
        printf("sin = %f, cos = %f, Accuracy = %f\n", sml_sin(degree), sml_cos(degree),
               sml_float_abs((sml_pow(sml_sin(degree), 2) + sml_pow(sml_cos(degree), 2))));
    }
    // note that using --fast-math will change the output since we are not using any platform/compiler-specific instructions
    // or any fancy tricks. This is pure math/skill issues.
    sml_throw_error(&err_conf, ERROR_OK, LOG_SEVERITY_INFO, "DONE!, %s", "With Style");

    return 0;
}
