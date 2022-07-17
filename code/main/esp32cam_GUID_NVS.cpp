/* Non-Volatile Storage (NVS) Read and Write a Value - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "guid-handler.h"
#include "guid-generator.h"

extern "C" void app_main(void)
{

    esp_err_t err = init_guid_storage();
    ESP_ERROR_CHECK(err);

    const char *guid = generate_uuid_v4().c_str();
    printf("original guid: %s\n", guid);

    err = set_guid(guid);
    ESP_ERROR_CHECK(err);

    char *guid_from_storage;
    err = get_guid(guid_from_storage);
    ESP_ERROR_CHECK(err);

    printf("from storage guid: %s\n", guid_from_storage);

    // guid module
    for (int i = 10; i >= 0; i--)
    {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
