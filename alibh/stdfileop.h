#pragma once

#if __cplusplus
extern "C" {
#endif

int remove(const char *path);
int rename(const char *oldname, const char *newname);

#if __cplusplus
}
#endif
