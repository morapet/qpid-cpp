/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#include "ReplicateLevel.h"
#include "qpid/Exception.h"
#include <iostream>

namespace qpid {
namespace ha {

using namespace std;

namespace {
const string S_NONE="none";
const string S_CONFIGURATION="configuration";
const string S_ALL="all";

string names[] = { S_NONE, S_CONFIGURATION, S_ALL };
}

bool replicateLevel(const string& level, ReplicateLevel& out) {
    if (level == S_NONE) { out = RL_NONE; return true; }
    if (level == S_CONFIGURATION) { out = RL_CONFIGURATION; return true; }
    if (level == S_ALL) { out = RL_ALL; return true; }
    return false;
}

ReplicateLevel replicateLevel(const string& level) {
    ReplicateLevel rl;
    if (!replicateLevel(level, rl))
        throw Exception("Invalid value for replication level: "+level);
    return rl;
}

string str(ReplicateLevel l) { return  names[l]; }

ostream& operator<<(ostream& o, ReplicateLevel rl) { return o << str(rl); }
istream& operator>>(istream& i, ReplicateLevel& rl) {
    string str;
    i >> str;
    rl = replicateLevel(str);
    return i;
}

}} // namespace qpid::ha
