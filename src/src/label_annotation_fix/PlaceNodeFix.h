/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
* Copyright 2015 Pelican Mapping
* http://osgearth.org
*
* osgEarth is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef OSGEARTH_ANNOTATION_PLACE_NODE_FIX_H
#define OSGEARTH_ANNOTATION_PLACE_NODE_FIX_H 1

#include <osgEarthAnnotation/OrthoNode>
#include <osgEarthSymbology/Style>

namespace osgEarth { namespace Annotation
{
    using namespace osgEarth;
    using namespace osgEarth::Symbology;

    /** 
     * A PlaceNodeFix combines an 2D icon, a label, support for mouse interaction
     * and a popup control (eventually)
     */
    class /*OSGEARTHANNO_EXPORT*/ PlaceNodeFix : public OrthoNode
    {
    public:
		META_AnnotationNode(osgEarthAnnotation, PlaceNodeFix);
		//META_AnnotationNodeAbstract(osgEarthAnnotation, PlaceNodeFix);

        /**
         * Constructs a new place node
         *
         * @param mapNode   MapNode that helps position this annotation
         * @param position  Initial location of the annotation
         * @param iconImage Image of the place icon
         * @param labelText Text to place next to the icon
         * @param style     Optional style settings.
         */
        PlaceNodeFix(
            MapNode*           mapNode,
            const GeoPoint&    position,
            osg::Image*        iconImage,
            const std::string& labelText,
            const Style&       style =Style() );

        /**
         * Constructs a new place node. You can specify an icon marker by
         * adding a IconSymbol to the Style.
         *
         * @param mapNode   MapNode that helps position this annotation
         * @param position  Initial location of the annotation
         * @param labelText Text to place next to the icon
         * @param style     Optional style settings.
         */
        PlaceNodeFix(
            MapNode*           mapNode,
            const GeoPoint&    position,
            const std::string& labelText,
            const Style&       style =Style() );

        /**
         * Constuct a new place node entirely from symbology
         *
         * @param mapNode   MapNode that helps position this annotation
         * @param position  Initial location of the annotation
         * @param style     Style settings.
         * @param dbOptions I/O options for embedded resource loading
         */
        PlaceNodeFix(
            MapNode*              mapNode,
            const GeoPoint&       position,
            const Style&          style,
            const osgDB::Options* dbOptions);

        /**
         * Deserializes a place node from Config data. (internal method)
         */
        PlaceNodeFix(
            MapNode*              mapNode,
            const Config&         conf,
            const osgDB::Options* dbOptions );

        /**
         * Image to use for the icon
         */
        void setIconImage(osg::Image* image);
        osg::Image* getIconImage() const { return _image.get(); }

        /**
         * Text label content
         */
        void setText( const std::string& text );
        virtual const std::string& getText() const { return _text; }

        /**
         * Style (for text and placement)
         */
        void setStyle( const Style& style );
        const Style& getStyle() const { return _style; }


    public: // OrthoNode override

        virtual void setAnnotationData( AnnotationData* data );

        virtual void setDynamic( bool value );

        virtual Config getConfig() const;

    protected:

        virtual ~PlaceNodeFix() { }
        
    private:
        osg::ref_ptr<osg::Image>           _image;
        std::string                        _text;
        Style                              _style;
        class osg::Geode*                  _geode;
        osg::ref_ptr<const osgDB::Options> _dbOptions;

        void init();

        // required by META_Node, but this object is not cloneable
        PlaceNodeFix() { }
        PlaceNodeFix(const PlaceNodeFix& rhs, const osg::CopyOp& op =osg::CopyOp::DEEP_COPY_ALL) : OrthoNode(rhs, op) { }
    };

} } // namespace osgEarth::Annotation

#endif //OSGEARTH_ANNOTATION_PLACE_NODE_FIX_H
