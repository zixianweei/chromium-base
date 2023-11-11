// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file was generated by:
//   tools/json_schema_compiler/compiler.py.
// NOTE: The format of types has changed. 'FooType' is now
//   'chrome.metricsPrivateIndividualApis.FooType'.
// Please run the closure compiler before committing changes.
// See https://chromium.googlesource.com/chromium/src/+/main/docs/closure_compilation.md

/**
 * @fileoverview Externs generated from namespace: metricsPrivateIndividualApis
 * @externs
 */

/** @const */
chrome.metricsPrivateIndividualApis = {};

/**
 * Records an action performed by the user.
 * @param {string} name
 * @see https://developer.chrome.com/extensions/metricsPrivateIndividualApis#method-recordUserAction
 */
chrome.metricsPrivateIndividualApis.recordUserAction = function(name) {};

/**
 * Records an elapsed time of no more than 3 minutes.  The sample value is
 * specified in milliseconds.
 * @param {string} metricName
 * @param {number} value
 * @see https://developer.chrome.com/extensions/metricsPrivateIndividualApis#method-recordMediumTime
 */
chrome.metricsPrivateIndividualApis.recordMediumTime = function(metricName, value) {};

/**
 * Records an enumeration value to the given metric. Analogous to
 * base::UmaHistogramEnumeration(). Use recordSparseValue for sparse enums or
 * enums not starting at 0.
 * @param {string} metricName
 * @param {number} value
 * @param {number} enumSize
 * @see https://developer.chrome.com/extensions/metricsPrivateIndividualApis#method-recordEnumerationValue
 */
chrome.metricsPrivateIndividualApis.recordEnumerationValue = function(metricName, value, enumSize) {};
