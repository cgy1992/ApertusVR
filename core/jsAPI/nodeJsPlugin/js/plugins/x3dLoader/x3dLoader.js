var utils = require('apertusvr/js/utils.js');
var ape = require('apertusvr/js/ape.js');
var cheerio = require('cheerio');
var fs = require('fs');
const uuidV1 = require('uuid/v1');
var self = this;

// IndexedFaceSet, IndexedLineSet

var nameCounter = 0;

exports.parseCoordIndexAttr = function(currentItem)
{
  var coordinates = new Array();
  var coordIndex = currentItem.attr('coordIndex');
  if (utils.isDefined(coordIndex)) {
    var indexArr = coordIndex.trim().split(' ');
    for (var i = 0; i < indexArr.length; i++) {
      coordinates.push(Number(indexArr[i]));
    }
  }
  return coordinates;
}

exports.parseColorIndexAttr = function(currentItem)
{
  var colorIndices = new Array();
  var colorIndex = currentItem.attr('colorIndex');
  if (utils.isDefined(colorIndex)) {
    var indexArr = colorIndex.trim().split(' ');
    for (var i = 0; i < indexArr.length; i++) {
      colorIndices.push(Number(indexArr[i]));
    }
  }
  return colorIndices;
}

exports.parseCoordinatePointAttr = function(currentItem)
{
  var pointsArr = new Array();
  var coordinate = currentItem.find('Coordinate').first();
  if (utils.isDefined(coordinate)) {
    var pointAttr = coordinate.attr('point');
    if (utils.isDefined(pointAttr)) {
      var lines = pointAttr.split('\n');
      for (var i = 0; i < lines.length; i++) {
        var line = lines[i].trim();
        var itemsArr = line.split(' ');
        for (var j = 0; j < itemsArr.length; j++) {
          pointsArr.push(Number(itemsArr[j]));
        }
      }
    }
  }
  return pointsArr;
}

// Transform

exports.parseTranslationAttr = function(currentItem)
{
  var translation = currentItem.attr('translation');
  if (utils.isDefined(translation)) {
    console.log(' - translation: ' + translation);
    var itemArr = translation.trim().split(' ');
      if (itemArr.length == 3) {
        return new ape.nbind.Vector3(Number(itemArr[0]), Number(itemArr[1]), Number(itemArr[2]));
      }
  }
  return new ape.nbind.Vector3();
}

exports.parseRotationAttr = function(currentItem)
{
  var rotation = currentItem.attr('rotation');
  if (utils.isDefined(rotation)) {
    console.log(' - rotation: ' + rotation);
    var itemArr = rotation.trim().split(' ');
    if (itemArr.length == 4) {
      return new ape.nbind.Quaternion(Number(itemArr[0]), Number(itemArr[1]), Number(itemArr[2]), Number(itemArr[3]));
    }
  }
  return new ape.nbind.Quaternion();
}

exports.parseScaleAttr = function(currentItem)
{
  var scale = currentItem.attr('scale');
  if (utils.isDefined(scale)) {
    console.log(' - scale: ' + scale);
    var itemArr = scale.trim().split(' ');
    if (itemArr.length == 3) {
      return new ape.nbind.Vector3(Number(itemArr[0]), Number(itemArr[1]), Number(itemArr[2]));
    }
  }
  return new ape.nbind.Vector3(1, 1, 1);
}

// ---

exports.parseItem = function(parentItem, currentItem, parentNodeObj)
{
  var typeName = currentItem[0].type;
  var tagName = currentItem[0].tagName || currentItem[0].name;
  var itemName = (currentItem[0].itemName || currentItem.attr('DEF') || 'item' + nameCounter);
  nameCounter++;
  currentItem[0].itemName = itemName;
  console.log(itemName + ' - ' + typeName + ' - ' + tagName);

  if (!typeName || !tagName) {
    console.log('currentItem has no typeName or tagName, returning.');
    return true; // continue;
  }

  if (typeName == 'tag') {
    if (tagName == '?xml') {
      //
    }
    else if (tagName == 'x3d') {
      //
    }
    else if (tagName == 'meta') {
      var name = currentItem.attr('name');
      if (utils.isDefined(name)) {
        console.log(' - name: ' + name);
        //  TODO: create a textGeometry
      }

      var content = currentItem.attr('content');
      if (utils.isDefined(content)) {
        console.log(' - content: ' + content);
        //  TODO: create a textGeometry
      }
    }
    else if (tagName == 'scene') {
      //
    }
    else if (tagName == 'worldinfo') {
      var info = currentItem.attr('info');
      if (utils.isDefined(info)) {
        console.log(' - info: ' + info);
        //  TODO: create a textGeometry
      }
    }
    else if (tagName == 'viewpoint') {
      //
    }
    else if (tagName == 'indexedfaceset') {
      var indexedFaceSetObj = ape.nbind.JsBindManager().createIndexedFaceSet(currentItem[0].itemName);
      console.log('indexedFaceSet is created with name: ' + currentItem[0].itemName);
      console.log(indexedFaceSetObj.getParameters().toString());

      var coordinatePointsArr = self.parseCoordinatePointAttr(currentItem);
      console.log(' - coordinate.point: ' + coordinatePointsArr);

      var coordIndexArr = self.parseCoordIndexAttr(currentItem);
      console.log(' - coordIndex: ' + coordIndexArr);

      var solid = currentItem.attr('solid');
      if (utils.isDefined(solid)) {
        console.log(' - solid: ' + solid);
      }

      indexedFaceSetObj.setParameters(coordinatePointsArr, coordIndexArr);
      console.log(indexedFaceSetObj.getParameters().toString());

      console.log('parentNodeObj: ' + parentNodeObj);
      if (parentNodeObj) {
        console.log('parentNodeObj is not NULL, setting parentNode to: ' + parentNodeObj.getName());
        indexedFaceSetObj.setParentNodeJsPtr(parentNodeObj);
      }
    }
    else if (tagName == 'indexedlineset') {
      var coordIndexArr = self.parseCoordIndexAttr(currentItem);
      console.log(' - coordIndex: ' + coordIndexArr);

      var colorIndexArr = self.parseCoordIndexAttr(currentItem);
      console.log(' - colorIndex: ' + colorIndexArr);

      var colorPerVertex = currentItem.attr('colorPerVertex');
      if (utils.isDefined(colorPerVertex)) {
        console.log(' - colorPerVertex: ' + colorPerVertex);
      }

      var coordinatePointsArr = self.parseCoordinatePointAttr(currentItem);
      console.log(' - coordinate.point: ' + coordinatePointsArr);
    }
    else if (tagName == 'transform') {
      var nodeObj = ape.nbind.JsBindManager().createNode(currentItem[0].itemName);
      console.log('node created with name: ' + nodeObj.getName());
      nodeLevel++;

      var position = self.parseTranslationAttr(currentItem);
      nodeObj.setPosition(position);
      console.log(nodeObj.getPosition().toString());

      var orientation = self.parseRotationAttr(currentItem);
      nodeObj.setOrientation(orientation);
      console.log(nodeObj.getOrientation().toString());

      var scale = self.parseScaleAttr(currentItem);
      nodeObj.setScale(scale);
      console.log(nodeObj.getScale().toString());

      console.log('parentNodeObj: ' + parentNodeObj);
      if (parentNodeObj) {
        console.log('parentNodeObj is not NULL, setting parentNode to: ' + parentNodeObj.getName());
        nodeObj.setParentNodeJsPtr(parentNodeObj);
      }

      return nodeObj;
    }
  }
}


var nodeLevelMap = {};
var nodeLevel = 0;
var nodeLevelTmp = 0;

exports.parseTree = function($, parentItem, childItem, parentNodeObj) {
  if (!childItem) {
    return;
  }
  var currentNode = self.parseItem(parentItem, childItem, parentNodeObj);
  if (currentNode) {
    nodeLevelMap[nodeLevel] = currentNode;
  }

  console.log('currentNode: ' + currentNode);
  console.log('nodeLevel: ' + nodeLevel);

  nodeLevelTmp = nodeLevel;

  $(childItem).children().each(function(i, elem) {
    var currentChild = $(this);
    self.parseTree($, $(currentChild).parent(), $(currentChild), nodeLevelMap[nodeLevel]);
  });

  if (currentNode) {
    nodeLevel = nodeLevel - 1;
  }

  return;
};

exports.parseX3D = function(x3dFilePath) {
  var $ = cheerio.load(fs.readFileSync(x3dFilePath), {
    xmlMode: true,
    lowerCaseTags: true
  });
  self.parseTree($, null, $('X3D'), null);
};
