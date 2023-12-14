#include "OutputFormats.h"

const std::map<std::string, OutputFormat> get_supported_output_formats() {
    return {{"vtu", OutputFormat::VTU}, {"xyz", OutputFormat::XYZ}, {"chkpt", OutputFormat::CHKPT}, {"none", OutputFormat::NONE}};
}