/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAINSCREENVIEWBASE_HPP
#define MAINSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>

class mainScreenViewBase : public touchgfx::View<mainScreenPresenter>
{
public:
    mainScreenViewBase();
    virtual ~mainScreenViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1_1;
    touchgfx::Image image1;
    touchgfx::ButtonWithLabel ifftButton;
    touchgfx::ButtonWithLabel dWaveButton;
    touchgfx::ScalableImage scalableImage1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<mainScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // MAINSCREENVIEWBASE_HPP
