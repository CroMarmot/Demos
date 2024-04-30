# Fastapi + Angular17 Demo

## Prepare

1. check port 4200 and 8000 is not used by other program
2. install python3, python3-pip, python3-venv
3. install node with nvm


## backend

```sh
python3 -m venv venv
. venv/bin/activate
pip install fastapi
pip install "uvicorn[standard]"
```

`app.py`

```py
from typing import Union

from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()


@app.get("/")
def read_root():
    return {"Hello": "World"}

class Item(BaseModel):
    name: str
    price: float


class ResponseMessage(BaseModel):
    message: str


@app.post("/api/items/", response_model=ResponseMessage)
async def create_item(item: Item):
    return {"message": "item received"}


@app.get("/api/items/", response_model=list[Item])
async def get_items():
    return [
        {"name": "Plumbus", "price": 3},
        {"name": "Portal Gun", "price": 9001},
    ]
```


```sh
uvicorn main:app --reload
```


## frontend


```sh
npm install -g @angular/cli
ng new frontend
cd frontend
npm install @hey-api/openapi-ts --save-dev
```

`frontend/package.json`

```diff
@@ -6,7 +6,8 @@
     "start": "ng serve",
     "build": "ng build",
     "watch": "ng build --watch --configuration development",
-    "test": "ng test"
+    "test": "ng test",
+    "generate-client": "openapi-ts --input http://localhost:8000/openapi.json --output ./src/client --client angular"
   },
   "private": true,
   "dependencies": {
```


```sh
npm run generate-client
```

`frontend/src/proxy.conf.json`

```json
{
  "/api": {
    "target": "http://localhost:8000",
    "secure": false
  }
}
```

`frontend/angular.json`

```diff
         },
         "serve": {
           "builder": "@angular-devkit/build-angular:dev-server",
+           "options": {
+             "proxyConfig": "src/proxy.conf.json"
+           },
           "configurations": {
             "production": {
               "buildTarget": "frontend:build:production"
```

`frontend/src/app/app.component.html`

```diff
 <!-- * * * * * * * * * * End of Placeholder  * * * * * * * * * * * * -->
 <!-- * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * -->

+<button (click)="getItems()">getItems</button>
+<button (click)="postItems()">postItems</button>
+
```


`frontend/src/app/app.component.ts`

```diff
git diff frontend/src/app/app.component.ts
 import { Component } from '@angular/core';
 import { CommonModule } from '@angular/common';
 import { RouterOutlet } from '@angular/router';
+import { DefaultService } from '../client';
+import { HttpClientModule } from '@angular/common/http';

 @Component({
   selector: 'app-root',
   standalone: true,
-  imports: [CommonModule, RouterOutlet],
+  imports: [CommonModule, RouterOutlet,HttpClientModule],
   templateUrl: './app.component.html',
-  styleUrl: './app.component.css'
+  styleUrl: './app.component.css',
+  providers:[DefaultService],
 })
 export class AppComponent {
   title = 'frontend';
+  constructor(private service: DefaultService){}
+  getItems() {
+    this.service.getItemsApiItemsGet().subscribe(o=>{
+      alert(JSON.stringify(o));
+    })
+  }
+  postItems() {
+    this.service.createItemApiItemsPost({requestBody:{name:'123',price:234}}).subscribe(o=>{
+      alert(JSON.stringify(o));
+    })
+  }
 }
```


```sh
ng serve
```

Then, click button