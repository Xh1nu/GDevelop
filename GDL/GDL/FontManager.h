/** \file
 *  Game Develop
 *  2008-2013 Florian Rival (Florian.Rival@gmail.com)
 */

#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

/**
 * \brief FontManager loads and manages SFML fonts.
 *
 * \ingroup ResourcesManagement
 */
class GD_API FontManager
{
public:

    /**
     * \brief Return a pointer to an SFML font.
     *
     * Example :
     * \code
     * sfmlText.SetFont(*fontManager->GetFont(fontName));
     * \endcode
     */
    const sf::Font * GetFont(const std::string & fontName);

    /**
     * \brief Unload all fonts from memory
     */
    void UnloadAllFonts();

    /**
     * \brief Return a pointer to the global singleton class
     */
    static FontManager *GetInstance()
    {
        if ( NULL == _singleton )
        {
            _singleton = new FontManager;
        }

        return ( static_cast<FontManager*>( _singleton ) );
    }

    /**
     * \brief Destroy the global singleton class.
     */
    static void DestroySingleton();

private:

    void EnsureDefaultFontIsLoaded();

    std::map < std::string, sf::Font* > fonts; ///< The font being loaded.
    sf::Font * defaultFont; ///< The default font used when no font is specified. Initialized at first use.

    FontManager() : defaultFont(NULL) {};
    virtual ~FontManager();

    static FontManager *_singleton;

};

#endif // FONTMANAGER_H

