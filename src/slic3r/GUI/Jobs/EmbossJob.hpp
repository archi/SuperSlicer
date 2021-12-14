#ifndef slic3r_EmbossJob_hpp_
#define slic3r_EmbossJob_hpp_

#include "libslic3r/Emboss.hpp"
#include "Job.hpp"

namespace Slic3r {
class ModelVolume;
class TriangleMesh;
}

namespace Slic3r::GUI {

struct EmbossData
{
    // Pointer on Data of font (glyph shapes)
    std::shared_ptr<Emboss::Font> font;
    // font item is not used for create object
    TextConfiguration text_configuration;
    // new volume name created from text
    std::string volume_name;

    // unique identifier of volume to change
    // I can't proove of alive pointer
    ModelVolume *volume;

    // unique identifier of volume to change
    // Change of volume change id, last change could disapear
    //ObjectID     volume_id;

    EmbossData(std::shared_ptr<Emboss::Font> font,
               TextConfiguration             text_configuration,
               std::string                   volume_name,
               ModelVolume *                 volume)
        : font(std::move(font))
        , text_configuration(text_configuration)
        , volume_name(volume_name)
        , volume(volume)
    {}
};

class EmbossJob : public Job
{
    std::unique_ptr<EmbossData> m_input;
    TriangleMesh                m_result;
public:
    EmbossJob(std::unique_ptr<EmbossData> input) : m_input(std::move(input)) {}
    void process(Ctl &ctl) override;
    void finalize(bool canceled, std::exception_ptr &) override;
};

} // namespace Slic3r::GUI

#endif // slic3r_EmbossJob_hpp_
