#ifndef BICUDO_API_UTIL_LOG_H
#define BICUDO_API_UTIL_LOG_H

#include <iostream>
#include <vector>
#include "bicudo/api/feature/feature.hpp"

namespace bicudo {
    void print(std::string_view);

    class logger : public bicudo::feature {
    protected:
        std::string tag {}, tag_processed {}, file_log_path {};
        std::vector<const char*> file_log {};

        bool debug {};
        bool gen_file_log {};
    public:
        logger(std::string_view);
        ~logger();

        void on_create() override;
        void on_destroy() override;

        void set_tag(std::string_view);
        std::string_view get_tag();

        void set_file_log_path(std::string_view);
        std::string_view get_file_log_path();

        void set_debug_mode(bool);
        bool is_debug_mode();

        void set_log_save_file(bool);
        bool is_log_save_file_enabled();

        void send_info(std::string_view);
        void send_warning(std::string_view);
    };

    struct timing {
        uint64_t elapsed_ticks {};
        uint64_t running_ticks {};
        bool checked {};
    };

    /*
     * Check timing difference since elapsed ticks, return true if is greater than specified ms.
     */
    bool reach(bicudo::timing&, uint64_t);

    /*
     * Reset timing elapsed ticks, always return true.
     */
    bool reset(bicudo::timing&);
}

#endif