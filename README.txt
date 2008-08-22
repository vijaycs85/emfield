/* $Id$ */

/*********************/
 Embedded Media Field
/*********************/

Author: Aaron Winborn (aaron)
Mainanters: aaron + Alex Urevick-Ackelsberg (Alex UA)
Development Began 2007-06-13

Requires: Drupal 5 or 6, Content (CCK)
Optional: Views, FeedAPI/FeedAPI Element Mapper (see this for instructions for importing Embedded Video Feeds: http://zivtech.com/blog/module-mashup-creating-a-feed-embedded-videos-using-emfield-feedapi-and-feedapimapper ), Media Actions, Asset, & Thickbox.

The Embedded Media Field creates a field for nodes created with CCK to accept pasted URL's or embed code from various third party media content providers, such as YouTube and Flickr. It will then parse the URL to determine the provider, and display the media appropriately.

Currently, the module ships with Embedded Video Field, Embedded Image Field, and Embedded Audio Field. In addition, it has Embedded Media Import, to import photosets and playlists into individual nodes, when allowed by specific providers. Finally, it also ships with Embedded Media Thumbnail, which allows editors to override provider-supplied thumbnails with their own custom image thumbnails.

The module also allows field & provider specific settings and overrides, such as autoplay, resized thumbnails or videos for teasers, RSS support, and YouTube's 'related videos'. You can turn off individual provider support on a field or global basis.

Currently supported providers:

Video:

    * Blip.TV
    * Brightcove
    * Daily Motion
    * Google
    * Guba
    * JumpCut
    * imeem
    * Lastfm
    * LiveVideo
    * MetaCafe
    * MySpace
    * Revver
    * SevenLoad
    * Spike.TV
    * Tudou
    * Veoh
    * Vimeo
    * YouTube
    * Local videos (when already uploaded in the files directory)

Image:

    * Flickr
    * ImageShack
    * PhotoBucket
    * Picasa

Audio:

    * Odeo
    * Podcast Alley
    * podOmatic

You can:

    * Administer emfield's general settings at administer >> content >> emfield
    * Add embedded media fields to your content types at administer >> content >> types >> %YourType% >> add_field
    * Manage teaser and full node display settings at administer >> content >> types >> %YourType% >> fields

For the most up-to-date documentation, please see http://drupal.org/node/184346