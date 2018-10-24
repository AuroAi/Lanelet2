#pragma once
#include <lanelet2_core/LaneletMap.h>
#include <string>
#include <vector>
#include "Configuration.h"
#include "Projection.h"

namespace lanelet {
using ErrorMessages = std::vector<std::string>;
/**
 * @brief Loads a lanelet map from a file.
 * @param filename name to load from. The extension decides how the file will be
 * parsed.
 * @param errors if this points to a valid object, errors occured during parsing
 * the map will be passed via this parameter. If this is nullptr, an exception
 * will be thrown if errors have occurred.
 * @param origin origin for the lat/lon -> x/y conversion (only used if
 * necessary for this specific format)
 * @param params optional params for loading. It depends on the parser that is
 * used which parameters are required. If no
 * params are passed, default values will be used
 * @return Loaded map. Pointer is aways valid. Otherwise, an exception will be
 * thrown
 * @throws lanelet2::IOError if the file did not exist, could not be parsed or
 * extension is not supported. If errors is not null, the loader will instead
 * try to recover and only throw on unrecoverable errors (ie if the map did not
 * exist). However, the loaded map will be incomplete if errors occurred.
 */
std::unique_ptr<LaneletMap> load(const std::string& filename, ErrorMessages* errors = nullptr,
                                 const Origin& origin = Origin::defaultOrigin(),
                                 const io::Configuration& params = io::Configuration());

/**
 * @brief Loads a lanelet map from a file.
 * @param filename name to load from. The extension decides how the file will be
 * parsed.
 * @param projector projection object for the transformations used
 * @param errors if not null, errors will be reported here instead of throwing
 * @param params optional params for loading. It depends on the parser that is
 * used which parameters are required. If no
 * params are passed, default values will be used
 * @return Loaded map. Pointer is aways valid. Otherwise, an exception will be
 * thrown
 * @throws lanelet2::IOError if the file did not exist, could not be parsed or
 * extension is not supported. If errors is not null, the loader will instead
 * try to recover and only throw on unrecoverable errors (ie if the map did not
 * exist). However, the loaded map will be incomplete if errors occurred.
 */
std::unique_ptr<LaneletMap> load(const std::string& filename, const Projector& projector,
                                 ErrorMessages* errors = nullptr,
                                 const io::Configuration& params = io::Configuration());

/**
 * @brief Loads a lanelet map from a file.
 * @param filename name to load from
 * @param parserName name of the parser to use. Available parsers can be
 * queried with supportedParsers()
 * @param errors if this points to a valid object, errors occured during parsing
 * the map will be passed via this parameter. If this is nullptr, an exception
 * will be thrown if errors have occurred.
 * @param origin origin object for the lat/lon -> x/y transformations
 * @param params optional params for loading. It depends on the parser that is
 * used which parameters are required. If no params are passed, default values
 * will be used
 * @return Loaded map. Pointer is aways valid. Otherwise, an exception will be
 * thrown
 * @throws lanelet2::IOError if the file did not exist, could not be parsed or
 * extension is not supported
 */
std::unique_ptr<LaneletMap> load(const std::string& filename, const std::string& parserName,
                                 ErrorMessages* errors = nullptr, const Origin& origin = Origin::defaultOrigin(),
                                 const io::Configuration& params = io::Configuration());

/**
 * @brief Loads a lanelet map from file.
 * @param filename name to load from
 * @param parserName name of the parser to use. Available parsers can be
 * queried with supportedParsers()
 * @param errors if this points to a valid object, errors occured during parsing
 * the map will be passed via this parameter. If this is nullptr, an exception
 * will be thrown if errors have occurred.
 * @param projector projection object for the transformations
 * @param params optional params for loading. It depends on the parser that is
 * used which parameters are required. If no
 * params are passed, default values will be used
 * @return Loaded map. Pointer is aways valid. Otherwise, an exception will be
 * thrown
 * @throws lanelet2::IOError if the file did not exist, could not be parsed or
 * extension is not supported
 */
std::unique_ptr<LaneletMap> load(const std::string& filename, const std::string& parserName, const Projector& projector,
                                 ErrorMessages* errors = nullptr,
                                 const io::Configuration& params = io::Configuration());

/**
 * @brief returns the names of the currently registered parsers (parsers from
 * plugins included)
 * @return list of names
 */
std::vector<std::string> supportedParsers();

/**
 * @brief returns the names of the currently supported extensions for parsing
 * (including the dot)
 * @return list of extensions
 * @addtogroup load
 */
std::vector<std::string> supportedParserExtensions();

/**
 * @brief writes a map to a file
 * @param filename file to write to (parent folders must exist!)
 * @param map map to be written
 * @param errors if this points to a valid object, errors occured during write
 * will be passed via this parameter. If this is nullptr, an exception will be
 * thrown if errors have occurred.
 * @param origin origin for x,y -> lat/lon conversion
 * @param params extra parameters for the writer (if required). If empty,
 * default parameters will be used.
 * @throws lanelet2::IOError if the file could not be created or writing failed.
 * If errors is not null, the writer will instead
 * try to recover and only throw on unrecoverable errors (ie if the file could
 * not be created). However, the written map will be incomplete if errors
 * occurred.
 */
void write(const std::string& filename, const lanelet::LaneletMap& map, ErrorMessages* errors = nullptr,
           const Origin& origin = Origin::defaultOrigin(), const io::Configuration& params = io::Configuration());

/**
 * @brief writes a map to a file
 * @param filename file to write to (parent folders must exist!). The extension
 * is used to deduce the format.
 * @param map map to be written
 * @param projector projector object for x,y -> lat/lon conversion
 * @param errors if this points to a valid object, errors occured during write
 * will be passed via this parameter. If this is nullptr, an exception will be
 * thrown if errors have occurred.
 * @param params extra parameters for the writer (if required). If empty,
 * default parameters will be used.
 * @throws lanelet2::IOError if the file could not be created or writing failed.
 */
void write(const std::string& filename, const LaneletMap& map, const Projector& projector,
           ErrorMessages* errors = nullptr, const io::Configuration& params = io::Configuration());

/**
 * @brief writes a map to a file
 * @param filename file to write to (parent folders must exist!). The extension
 * is used to deduce the format.
 * @param map map to be written
 * @param writerName name of the writer format to use. Available writers can be
 * queried with supportedWriters().
 * @param errors if this points to a valid object, errors occured during write
 * will be passed via this parameter. If this is nullptr, an exception will be
 * thrown if errors have occurred.
 * @param origin origin definition for x,y -> lat/lon conversion
 * @param params extra parameters for the writer (if required). If empty,
 * default parameters will be used.
 * @throws lanelet2::IOError if the file could not be created or writing failed.
 */
void write(const std::string& filename, const lanelet::LaneletMap& map, const std::string& writerName,
           ErrorMessages* errors = nullptr, const Origin& origin = Origin::defaultOrigin(),
           const io::Configuration& params = io::Configuration());

/**
 * @brief writes a map to a file
 * @param filename file to write to (parent folders must exist!). The extension
 * is used to deduce the format.
 * @param map map to be written
 * @param writerName name of the writer format to use. Available writers can be
 * queried with supportedWriters().
 * @param projector projector object for x,y -> lat/lon conversion
 * @param errors if this points to a valid object, errors occured during write
 * will be passed via this parameter. If this is nullptr, an exception will be
 * thrown if errors have occurred.
 * @param params extra parameters for the writer (if required). If empty,
 * default parameters will be used.
 * @throws lanelet2::IOError if the file could not be created or writing failed.
 */
void write(const std::string& filename, const LaneletMap& map, const std::string& writerName,
           const Projector& projector, ErrorMessages* errors = nullptr,
           const io::Configuration& params = io::Configuration());

/**
 * @brief returns the names of the currently registered writing (writers from
 * plugins included)
 * @return list of names
 */
std::vector<std::string> supportedWriters();

/**
 * @brief returns the names of the currently supported extensions for writing
 * (including the dot)
 * @return list of extensions
 */
std::vector<std::string> supportedWriterExtensions();
}  // namespace lanelet
