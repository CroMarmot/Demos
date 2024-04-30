from typing import Union

from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()


@app.get("/")
def read_root():
    return {"Hello": "World"}


# @app.get("/items/{item_id}")
# def read_item(item_id: int, q: Union[str, None] = None):
#     return {"item_id": item_id, "q": q}

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
