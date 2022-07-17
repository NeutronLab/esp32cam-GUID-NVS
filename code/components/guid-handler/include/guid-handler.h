#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "nvs_handle.hpp"
#include "guid-generator.h"

#define GUID_KEY "GUID"
#define STORAGE_NAMESPACE "storage"

/* Initialize the storage for further operations
on device guid, current implementation uses nvs.
 */
esp_err_t init_guid_storage();
/* Read device guid from nvs
 */
esp_err_t get_guid(char *&guid);
/* set device guid from nvs
 */
esp_err_t set_guid(const char *guid);