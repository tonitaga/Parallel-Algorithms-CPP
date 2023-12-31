#ifndef A3_PARALLELS_MODEL_ANT_COLONY_ANT_ANT_PATH_H_
#define A3_PARALLELS_MODEL_ANT_COLONY_ANT_ANT_PATH_H_

#include <vector>

namespace ng {
    struct AntPath final {
        std::vector<std::size_t> vertices;
        double distance = 0;
    };
}  // namespace ng

#endif  // A3_PARALLELS_MODEL_ANT_COLONY_ANT_ANT_PATH_H_
