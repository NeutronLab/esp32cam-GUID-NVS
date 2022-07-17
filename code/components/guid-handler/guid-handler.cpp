#include "guid-handler.h"
#include <string.h>
#include <stdio.h>

esp_err_t init_guid_storage()
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    return err;
}

esp_err_t get_guid(char *&guid)
{
    nvs_handle_t my_handle;
    esp_err_t err;

    // Open
    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
        return err;

    size_t required_size = GUID_LENGTH * sizeof(char) + 1;
    char *guid_from_nvs = (char *)malloc(required_size);
    err = nvs_get_str(my_handle, GUID_KEY, guid_from_nvs, &required_size);
    if (err != ESP_OK)
    {
        free(guid_from_nvs);
        return err;
    }

    if (guid_from_nvs == NULL)
    {
        return ESP_FAIL;
    }

    if (guid_from_nvs[strlen(guid_from_nvs) - 1] != '\0')
    {
        guid_from_nvs[strlen(guid_from_nvs) - 1] = '\0';
    }

    guid = guid_from_nvs;

    // Close
    nvs_close(my_handle);
    return ESP_OK;
}

esp_err_t set_guid(const char *guid)
{
    nvs_handle_t my_handle;
    esp_err_t err;

    // Open
    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
        return err;
    // size_t required_size = GUID_LENGTH * sizeof(char);
    err = nvs_set_str(my_handle, GUID_KEY, guid);

    if (err == ESP_ERR_NVS_VALUE_TOO_LONG)
    {
        printf("err guid-handler: ESP_ERR_NVS_VALUE_TOO_LONG");
    }
    else if (err == ESP_ERR_NVS_NOT_ENOUGH_SPACE)
    {
        printf("err guid-handler: ESP_ERR_NVS_NOT_ENOUGH_SPACE");
    }

    if (err != ESP_OK)
        return err;

    // Commit
    err = nvs_commit(my_handle);
    if (err != ESP_OK)
        return err;

    // Close
    nvs_close(my_handle);
    return ESP_OK;
}
