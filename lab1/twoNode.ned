//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

network TwoNode
{
    @display("bgb=268,138");
    submodules:
        Node1: Node {
            id = 1;
            @display("p=32.66,70.29");
        }
        Node2: Node {
            id = 2;
            @display("p=225.78,70.29");
        }

    connections:
        Node1.out --> Node2.in;
        Node2.out --> Node1.in;
}
