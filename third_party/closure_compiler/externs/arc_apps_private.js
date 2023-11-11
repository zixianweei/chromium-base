// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file was generated by:
//   tools/json_schema_compiler/compiler.py.
// NOTE: The format of types has changed. 'FooType' is now
//   'chrome.arcAppsPrivate.FooType'.
// Please run the closure compiler before committing changes.
// See https://chromium.googlesource.com/chromium/src/+/main/docs/closure_compilation.md

/**
 * @fileoverview Externs generated from namespace: arcAppsPrivate
 * @externs
 */

/** @const */
chrome.arcAppsPrivate = {};

/**
 * @typedef {{
 *   packageName: string
 * }}
 */
chrome.arcAppsPrivate.AppInfo;

/**
 * Returns info of the installed ARC apps that are launchable, including ready
 * and non-ready apps.
 * @param {function(!Array<!chrome.arcAppsPrivate.AppInfo>): void} callback
 */
chrome.arcAppsPrivate.getLaunchableApps = function(callback) {};

/**
 * Launches the ARC app with its package name. The app is launched immediately
 * if it's ready, otherwise it will be launched when it becomes ready. The
 * callback is called as soon as the launch is scheduled.
 * @param {string} packageName
 * @param {function(): void=} callback
 */
chrome.arcAppsPrivate.launchApp = function(packageName, callback) {};

/**
 * Fires when a new app can be launched via $(ref:launchApp).
 * @type {!ChromeEvent}
 */
chrome.arcAppsPrivate.onInstalled;
