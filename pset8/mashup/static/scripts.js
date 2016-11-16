// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

//marker image
var MARKER_IMG = "/static/marker.png";

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [{
                visibility: "off"
            }]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [{
                visibility: "off"
            }]
        }

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {
            lat: 61.7611,
            lng: -157.3125
        }, // Stanford, California
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true,
        mapTypeControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place) {
    // TODO
    var marker = new google.maps.Marker({
        position: {
            lat: place.latitude,
            lng: place.longitude
        },
        label: place.place_name + ", " + place.admin_name1,
        icon: {
            labelOrigin: new google.maps.Point(16, 40),
            url: MARKER_IMG
        }
    });

    marker.addListener('click', function() {

        //show spinner 
        showInfo(marker);

        var parameters;

        if (place.country_code == null) {
            parameters = {
                geo: place.place_name,
                lang: "ru_ua"
            };
        }
        else if (place.country_code == "US") {
            parameters = {
                geo: place.postal_code
            };
        }
        else {
            parameters = {
                geo: place.place_name,
                lang: place.country_code
            };
        }

        //get data    
        $.getJSON(Flask.url_for("articles"), parameters)
            .done(function(data, textStatus, jqXHR) {
                if (data.length == 0) {
                    showInfo(marker, "No news");
                }
                else {
                    content = "";
                    for (var i = 0; i < data.length; i++) {
                        content += "<li><a href=" + data[i]["link"] + " target=\"_blank\">" + data[i]["title"] + "</a></li>"
                    }
                    content = "<ul>" + content + "</ul>"
                    showInfo(marker, content);
                }
            })
            .fail(function(jqXHR, textStatus, errorThrown) {

                // log error to browser's console
                console.log(errorThrown.toString());
            });
    });

    markers.push(marker);
}

/**
 * Show markers.
 */
function showMarkers() {
    setMapForMarkers(map);
}

/**
 * Configures application.
 */
function configure() {
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {

        // if info window isn't open
        // http://stackoverflow.com/a/12410385
        if (!info.getMap || !info.getMap()) {
            update();
        }
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // configure typeahead
    $("#q").typeahead({
        highlight: false,
        minLength: 1
    }, {
        display: function(suggestion) {
            return null;
        },
        limit: 10,
        source: search,
        templates: {
            suggestion: Handlebars.compile(
                "<div>" +
                "{{place_name}}, {{admin_name1}}, {{postal_code}}" +
                "</div>"
            )
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // set map's center
        map.setCenter({
            lat: parseFloat(suggestion.latitude),
            lng: parseFloat(suggestion.longitude)
        });

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        info.close();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true;
        event.stopPropagation && event.stopPropagation();
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Removes markers from map.
 */
function removeMarkers() {
    // TODO
    setMapForMarkers(null);
    markers.length = 0;
}

/**
 * set map for markers .
 */
function setMapForMarkers(map) {
    for (var i = 0; i < markers.length; i++) {
        markers[i].setMap(map);
    }
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, syncResults, asyncResults) {
    // get places matching query (asynchronously)
    var parameters = {
        q: query
    };
    $.getJSON(Flask.url_for("search"), parameters)
        .done(function(data, textStatus, jqXHR) {

            // call typeahead's callback with search results (i.e., places)
            asyncResults(data);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {

            // log error to browser's console
            console.log(errorThrown.toString());

            // call typeahead's callback with no results
            asyncResults([]);
        });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content) {
    // start div
    var div = "<div id='info'>";
    if (typeof(content) == "undefined") {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='/static/ajax-loader.gif'/>";
    }
    else {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() {
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();
    var centr = bounds.getCenter();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng(),
        centr: centr.lat() + "," + centr.lng()
    };

    $.getJSON(Flask.url_for("update"), parameters)
        .done(function(data, textStatus, jqXHR) {

            // remove old markers from map
            removeMarkers();

            // add new markers to map
            for (var i = 0; i < data.length; i++) {
                addMarker(data[i]);
            }

            // show all new markers
            showMarkers();
        })
        .fail(function(jqXHR, textStatus, errorThrown) {

            // log error to browser's console
            console.log(errorThrown.toString());
        });
};
