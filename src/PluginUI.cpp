/*
 * Elements plugin example
 * Copyright (C) 2022 Filipe Coelho <falktx@falktx.com>
 * SPDX-License-Identifier: ISC
 */

#include "DistrhoUI.hpp"
#include "ResizeHandle.hpp"

START_NAMESPACE_DISTRHO

using namespace cycfi::elements;

// --------------------------------------------------------------------------------------------------------------------

class ElementsPluginUI : public UI
{
    ResizeHandle fResizeHandle;

    // ----------------------------------------------------------------------------------------------------------------

    using knob_ptr = std::shared_ptr<dial_base>;
    knob_ptr knobs[3];

    auto make_knob_cutoff()
    {
        knobs[kParameter_cutoff] = share(
            dial(
                radial_marks<20>(basic_knob<90>()),
                0.f
            )
        );

        return align_center_middle(
            vtile(
                radial_labels<15>(
                    hold(knobs[kParameter_cutoff]),
                    1.f,
                    "20 Hz", "20 kHz"
                ),
                label("Cutoff")
            )
        );
    }

    auto make_knob_q()
    {
        knobs[kParameter_q] = share(
            dial(
                radial_marks<20>(basic_knob<90>()),
                0.f
            )
        );

        return align_center_middle(
            vtile(
                radial_labels<15>(
                    hold(knobs[kParameter_q]),
                    1.f,
                    "0.5", "10"
                ),
                label("Q")
            )
        );
    }

    auto make_knobs()
    {
        return htile(
            make_knob_cutoff(),
            make_knob_q()
        );
    }

    // ----------------------------------------------------------------------------------------------------------------

public:
   /**
      UI class constructor.
      The UI should be initialized to a default state that matches the plugin side.
    */
    ElementsPluginUI()
        : UI(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT),
          fResizeHandle(this)
    {
        // set minimum size constraints and automatically sale
        setGeometryConstraints(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT, false, true);

        // hide handle if UI is resizable
        if (isResizable())
            fResizeHandle.hide();

        // get background color from host if available
        color bgcolor;
        if (const uint hostbg = getBackgroundColor())
            bgcolor = rgba((hostbg >> 24) & 0xff, (hostbg >> 16) & 0xff, (hostbg >>  8) & 0xff, 0xff);
        else
            bgcolor = rgba(35, 35, 37, 255);

        // here come the elements
        content(
            margin({ 20, 10, 20, 10 },
                vmin_size(200,
                    htile(
                        hstretch(0.5, margin({ 20, 20, 20, 20 }, pane(DISTRHO_PLUGIN_NAME, make_knobs(), 1.5f)))
                    )
                )
            ),
            box(bgcolor)
        );
        
        // start UI in default state
        parameterChanged(kParameter_cutoff, kParameterRanges[kParameter_cutoff].def);
        parameterChanged(kParameter_q, kParameterRanges[kParameter_q].def);

        // knob change listeners
        knobs[kParameter_cutoff]->on_change = [this](double val) {
            // TODO log scale
            const double unnomal = kParameterRanges[kParameter_cutoff].min
                                 + val * (kParameterRanges[kParameter_cutoff].max - kParameterRanges[kParameter_cutoff].min);
            setParameterValue(kParameter_cutoff, unnomal);
        };
        knobs[kParameter_q]->on_change = [this](double val) {
            const double unnomal = kParameterRanges[kParameter_q].min 
                                 + val * (kParameterRanges[kParameter_q].max - kParameterRanges[kParameter_q].min)    ;
            setParameterValue(kParameter_q, unnomal);
        };
    }

protected:
    // ----------------------------------------------------------------------------------------------------------------
    // DSP/Plugin Callbacks

   /**
      A parameter has changed on the plugin side.@n
      This is called by the host to inform the UI about parameter changes.
    */
    void parameterChanged(uint32_t index, float value) override
    {
        DISTRHO_SAFE_ASSERT_RETURN(index < kParameterCount,);

        // TODO log scale
        const float normalized = (value - kParameterRanges[index].min)
                               / (kParameterRanges[index].max - kParameterRanges[index].min);

        knobs[index]->dial_base::value(normalized);
        refresh(*knobs[index]);
    }

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ElementsPluginUI)
};

// --------------------------------------------------------------------------------------------------------------------

UI* createUI()
{
    return new ElementsPluginUI();
}

// --------------------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
